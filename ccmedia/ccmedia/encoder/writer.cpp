#include "writer.hpp"

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
