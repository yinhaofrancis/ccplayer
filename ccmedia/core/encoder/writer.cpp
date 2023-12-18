#include <sys/time.h>

#include "writer.hpp"
using namespace cc;

cc::writer::writer(const char *path) : m_audio_encoder(AV_SAMPLE_FMT_FLTP, 1, 22050), m_video_encoder(640, 360)
{
    int err = avformat_alloc_output_context2(&m_format_ctx, nullptr, nullptr, path);
    m_path = path;
    if (err)
    {
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

void writer::transform(const char *from)
{
    this->transform_runner = new runner<writer, true>([this, from](auto &r)
                                                      { this->transform_run(r, from); });
    this->transform_runner->run();
}

void writer::transform_run(runner<writer, true> &r, const char *from)
{
    format n_format(from);
    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    avio_open(&m_format_ctx->pb, m_path, AVIO_FLAG_WRITE);
    unsigned long audio_tick = 0;
    unsigned long video_tick = 0;
    int err = avformat_write_header(m_format_ctx, nullptr);
    if (err != 0)
    {
        throw error(err);
    }

    while (!r.is_close())
    {
        try
        {
            n_format.read(packet);
        }
        catch (error e)
        {
            if(e.code == AVERROR_EOF){
                std::cout << "e" <<std::endl;
                break;
            }
        }
        if (packet->stream_index == n_format.audio_index())
        {
            try
            {
                n_format.decode_audio_core(frame, packet);
                audio_tick += packet->duration;
                m_audio_encoder.encode(frame, packet);
                packet->stream_index = n_format.audio_index();
                
                // std::cout <<  packet->dts << std::endl;
                av_write_frame(m_format_ctx, packet);
            }
            catch (const error &e)
            {
                if(e.code == AVERROR(EAGAIN)){
                    continue;
                }else{
                    std::cout << "e " << e.code <<e.msg <<std::endl;
                    break;
                }
            }
        }
        else if (packet->stream_index == n_format.video_index())
        {
            try
            {
                n_format.decode_video_core(frame, packet);
                m_video_encoder.encode(frame, packet);
                packet->stream_index = n_format.video_index();
                video_tick += packet->duration;
                av_write_frame(m_format_ctx, packet);
            }
            catch (const error &e)
            {
                if(e.code == AVERROR(EAGAIN)){
                    continue;
                }else{
                    std::cout << "e" <<std::endl;
                    break;
                }
            }
        }
    }
    av_write_trailer(m_format_ctx);
    avio_closep(&this->m_format_ctx->pb);
    av_frame_free(&frame);
    av_packet_free(&packet);
    r.close();
}

unsigned long writer::get_current_tick(){
    struct timeval tv;
    if(gettimeofday(&tv,NULL ) != 0){
        return 0;
    }

    return (tv.tv_sec* 1000 + tv.tv_usec /1000);
}