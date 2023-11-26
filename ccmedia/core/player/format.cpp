//
//  format.cpp
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#include "format.hpp"

using namespace cc;

void cc::global_prepare()
{
    av_register_all();
    avcodec_register_all();
}


format::format(const char *localPath){
    this->m_path = localPath;
    this->m_format_ctx = avformat_alloc_context();

    int err = avformat_open_input(&m_format_ctx, localPath, NULL, NULL);
    if (0 != err){
        throw error(err);
    }

    load_codec();
}

void cc::format::load_codec()
{
    m_audio_index = -1;
    m_video_index = -1;
    for (int i = 0; i < m_format_ctx->nb_streams; i++)
    {
        auto stream = m_format_ctx->streams[i];
        auto parm = stream->codecpar;
        if (parm->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            av_dump_format(m_format_ctx, i, this->m_path.c_str(), 0);
            try
            {
                m_video_codec.config(parm->codec_id, parm);
            }
            catch (error)
            {
                continue;
            }
            m_video_index = i;
        }
        if (parm->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            av_dump_format(m_format_ctx, i, this->m_path.c_str(), 0);
            try
            {
                m_audio_codec.config(parm->codec_id, parm);
            }
            catch (error)
            {
                continue;
                ;
            }
            m_audio_index = i;
        }
    }
}

format::~format(){
    if(this->m_format_ctx != nullptr){
        avformat_close_input(&this->m_format_ctx);
        avformat_free_context(this->m_format_ctx);
    }
    
}


AVRational& format::video_timebase(){
    return m_format_ctx->streams[m_video_index]->time_base;
}

AVRational& format::audio_timebase(){
    return m_format_ctx->streams[m_audio_index]->time_base;
}

double format::video_timestamp_transform(int64_t pts){
    return pts * av_q2d(this->video_timebase());
}

double format::audio_timestamp_transform(int64_t pts){
    return pts * av_q2d(this->audio_timebase());
}

void format::codec::config(AVCodecID codec_id,AVCodecParameters *param){
    this->p_codec = avcodec_find_decoder(codec_id);
    
    if(this->p_codec == nullptr){
        throw error(std::string("find codec fail"), 0);
    }
    
    this->p_ctx = avcodec_alloc_context3(this->p_codec);
    
    if(this->p_ctx == nullptr){
        throw error(std::string("alloc codec context fail"), 0);
    }
    int err = avcodec_parameters_to_context(this->p_ctx, param);
    if(err < 0){
        throw error(err);
    }
    
    err = avcodec_open2(this->p_ctx, this->p_codec, nullptr);
    if(err < 0){
        throw error(err);
    }
}

void format::flush(){
    avcodec_flush_buffers(this->m_audio_codec.p_ctx);
    avcodec_flush_buffers(this->m_video_codec.p_ctx);
}

format::codec::codec(){}

format::codec::~codec(){
    if(this->p_ctx != nullptr){
        avcodec_close(this->p_ctx);
        avcodec_free_context(&this->p_ctx);
    }
}

AVPacket* format::read(){
    
    auto packet = av_packet_alloc();
    try
    {
        read(packet);
        return packet;
    }
    catch(error e)
    {
        av_packet_free(&packet);
        throw e;
    }
}
void format::read(AVPacket* packet){
    read_lock.lock();
    int err = av_read_frame(m_format_ctx, packet);
    read_lock.unlock();
    if(err != 0){
        throw error(err);
    }
}
void format::decode_video_core(AVFrame *frame, AVPacket *packet) {
    int err = avcodec_send_packet(m_video_codec.p_ctx, packet);
    if (err != 0){
        throw error(err);
    }
    err = avcodec_receive_frame(m_video_codec.p_ctx, frame);
    if(err != 0){
        throw error(err);
    }
}

void format::decode_audio_core(AVFrame *frame, AVPacket *packet) {
    int err = avcodec_send_packet(m_audio_codec.p_ctx, packet);
    if (err != 0){
        throw error(err);
    }
    err = avcodec_receive_frame(m_audio_codec.p_ctx, frame);
    if(err != 0){
        throw error(err);
    }
}
void format::seek(double ts,double max,bool grow){
    read_lock.lock();
    avformat_seek_file(m_format_ctx, -1, 0, ts * AV_TIME_BASE, INT64_MAX,AVSEEK_FLAG_FRAME);
    read_lock.unlock();
}
