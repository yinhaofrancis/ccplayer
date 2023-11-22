//
//  Audio.cpp
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#include "audio.hpp"


using namespace cc;

AudioPlayerState audio_player::state(){
    ALint stateVaue = 0;
    alGetSourcei(m_source, AL_SOURCE_STATE, &stateVaue);
    if(stateVaue == AL_PLAYING){
        return audio_play_playing;
    }else if (stateVaue == AL_PAUSED){
        return audio_play_pausing;
    }else if (stateVaue == AL_STOPPED){
        return audio_play_stoped;
    }else{
        return audio_play_initial;
    }
}

void audio_player::render(AVFrame * frames){
    
    auto buffer = create_audio_buffer(frames);
    send_buffer(buffer);
    dequeue_buffer();
}
AudioBuffer audio_player::create_audio_buffer(AVFrame *frame) {
    if(m_source == 0){
        
        alGenSources(1, &m_source);
        alSpeedOfSound(1.0);
        alDopplerVelocity(1.0);
        alDopplerFactor(1.0);
        alSourcef(m_source, AL_PITCH, 1.0f);
        alSourcef(m_source, AL_GAIN, 1.0f);
        alSourcei(m_source, AL_LOOPING, AL_FALSE);
        alSourcef(m_source, AL_SOURCE_TYPE, AL_STREAMING);
        alSourcef(m_source, AL_CHANNELS, 2);
        
    }
    auto out_buffer_size = av_samples_get_buffer_size(NULL, frame->channels, frame->nb_samples, AV_SAMPLE_FMT_S16, 0);
    uint8_t* out[] = {(uint8_t*)malloc(out_buffer_size),0};
    swr_convert(this->m_audio_swr_context, out, frame->nb_samples, (const uint8_t **)frame->data, frame->nb_samples);
    AudioBuffer buffer;
    buffer.size = out_buffer_size;
    buffer.buffer = out[0];
    buffer.format = AL_FORMAT_STEREO16;
    buffer.freg = frame->sample_rate;
    return buffer;
}

void audio_player::push_back(AVFrame * frame){
    AudioBuffer buffer = create_audio_buffer(frame);
    this->play_buffer.push_back(buffer);
}

void audio_player::send_buffer() {

    int sum = 0;
    int offset = 0;
    ALuint buf = 0;
    alGenBuffers(1, &buf);
    
    for (auto v : play_buffer) {
        sum += v.size;
    }
    uint8_t* m = (uint8_t*)malloc(sum);
    
    for (auto v : play_buffer) {
        
        memcpy(m + offset, v.buffer, v.size);
        
        free(v.buffer);
        
        offset += v.size;
    }
    alBufferData(buf, play_buffer.front().format, m , sum, play_buffer.front().freg);
    play_buffer.clear();
    alSourceQueueBuffers(m_source, 1, &buf);
    free(m);
    
}
void audio_player::send_buffer(AudioBuffer& buffer) {


    ALuint buf = 0;
    alGenBuffers(1, &buf);
    alBufferData(buf, buffer.format, buffer.buffer , buffer.size, buffer.freg);
    free(buffer.buffer);
    alSourceQueueBuffers(m_source, 1, &buf);
    if(this->state() != audio_play_playing){
        alSourcePlay(m_source);
    }
    
}
void audio_player::commit(){
    while(this->buffer_count() < 10 && this->play_buffer.size() > 0){
        this->send_buffer();
    }
    if(this->state() != audio_play_playing){
        alSourcePlay(m_source);
    }
}

void audio_player::dequeue_buffer() {
    if(m_source == 0){
        return;
    }
    
    ALint buffersProcessed = 0;
    alGetSourcei(this->m_source, AL_BUFFERS_PROCESSED, &buffersProcessed);
    

    while (buffersProcessed > 0) {
        ALuint buffer;
        alSourceUnqueueBuffers(this->m_source, 1, &buffer);
        alDeleteBuffers(1, &buffer);
        buffersProcessed --;
    }
    
}

int audio_player::buffer_count(){
    ALint queuedBuffers;
    alGetSourcei(m_source, AL_BUFFERS_QUEUED, &queuedBuffers);
    return queuedBuffers;
}

void audio_player::pause(){
    alSourcePause(m_source);
}

float audio_player::sec(){
    ALfloat ssec;
    alGetSourcef(m_source, AL_SEC_OFFSET, &ssec);
    return ssec;
}

audio_player::audio_player(){
    m_device = alcOpenDevice(NULL);
    m_context = alcCreateContext(m_device, NULL);
    alcMakeContextCurrent(m_context);
 
}
void audio_player::config(AVCodecContext &ctx){
    if(this->m_audio_swr_context == nullptr){
        this->m_audio_swr_context = swr_alloc();
        swr_alloc_set_opts(this->m_audio_swr_context,
                           av_get_default_channel_layout(this->channels),
                           AV_SAMPLE_FMT_S16,
                           ctx.sample_rate,
                           av_get_default_channel_layout(ctx.channels),
                           ctx.sample_fmt,
                           ctx.sample_rate, 0, nullptr);
        swr_init(this->m_audio_swr_context);
    }
}

void audio_player::rate(double rate){
    alSourcef(m_source, AL_PITCH, rate);
}


audio_player::~audio_player(){
    
    alSourceStop(m_source);
    if(this->m_audio_swr_context != nullptr){
        swr_free(&this->m_audio_swr_context);
    }
    dequeue_buffer();
    alDeleteSources(1, &m_source);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
    if (play_buffer.size() > 0){
        for (auto v : play_buffer) {
            free(v.buffer);
        }
    }
}


