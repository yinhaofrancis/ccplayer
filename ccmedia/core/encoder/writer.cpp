#include "writer.hpp"
using namespace cc;

cc::writer::writer(const char *path):m_audio_encoder(AV_SAMPLE_FMT_S16,2,44100),m_video_encoder(1280,720)
{
    int err = avformat_alloc_output_context2(&m_format_ctx,nullptr,nullptr,path);
    if(err){
        throw cc::error(err);
    }
    m_audio_encoder.open();
    m_video_encoder.open();
    m_audio_encoder.load_stream(m_format_ctx);
    m_video_encoder.load_stream(m_format_ctx);
    
}

cc::writer::~writer()
{
    avformat_free_context(m_format_ctx);
} 

void writer::transform(const char *from){
    this->transform_runner = new runner<writer,true>([this,from](auto& r){
        this->transform_run(r,from);
    });
    
}

void writer::transform_run(runner<writer,true>& r,const char *from){
    format n_format(from);
    AVPacket* packet = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();

    while (r.is_close())
    {
        try
        {
            n_format.read(packet);
            if(packet->stream_index == n_format.audio_index()){
                n_format.decode_audio_core(frame,packet);
            }else if (packet->stream_index == n_format.video_index()){
                n_format.decode_video_core(frame,packet);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            r.sleep_millisec(10);
            continue;
        }
    }
    av_frame_free(&frame);
    av_packet_free(&packet);
}