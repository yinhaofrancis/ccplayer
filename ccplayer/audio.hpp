//
//  Audio.hpp
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#ifndef Audio_hpp
#define Audio_hpp

#include "cc_util.hpp"



namespace cc {



struct AudioBuffer{
    ALsizei freg;
    ALsizei size;
    ALvoid *buffer;
    ALenum format;
};
enum AudioPlayerState{
    audio_play_playing,
    audio_play_stoped,
    audio_play_pausing,
    audio_play_initial
};


class audio_player{
    ALCdevice* m_device;
    ALCcontext* m_context;
    ALuint m_source;
    
    std::list<AudioBuffer> play_buffer;
    
    std::mutex m_lock;
    
    void send_buffer(AudioBuffer &);
    
    void send_buffer();
    
    SwrContext* m_audio_swr_context;
    
    const int m_channels = 2;
    
    const ALenum m_format = AL_FORMAT_STEREO16;
    
    AudioBuffer create_audio_buffer(AVFrame *frame);
    
    void push_back(AVFrame * frame);
    
    void commit();
    
public:
    
    
    audio_player();
    
    void config(AVCodecContext& ct);
    
    ~audio_player();
    
    void render(AVFrame *frames);
    
    void pause();
    
    void rate(double rate);
    
    float sec();
    
    AudioPlayerState state();
    
    int buffer_count();
    
    void dequeue_buffer();
    
};





};






#endif /* Audio_hpp */
