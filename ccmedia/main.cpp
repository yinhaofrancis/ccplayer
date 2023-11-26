#include "core/encoder/encoder.hpp"
#include "core/player/format.hpp"

int main()
{

    AVFrame *frame = av_frame_alloc();
    AVPacket *packet = av_packet_alloc();
    AVPacket *packet2 = av_packet_alloc();
    cc::global_prepare();  
    cc::format m_format("/Users/haoyin/Documents/gamesci_2022PV03.mp4");
    
    cc::encoder m(1280, 720);
    m.open();
    m_format.load_codec();
    bool is_close = false;
    while (!is_close)
    {
        try
        {
            m_format.read(packet);
            if (packet->stream_index == m_format.video_index())
            {
                m_format.decode_video_core(frame,packet);
                std::cout<< av_get_picture_type_char(frame->pict_type)<<std::endl;
                m.encode(frame,packet2);
                std::cout<< packet2->pts<<std::endl;
            }
        }
        catch(cc::error e)
        {
            if (e.code == AVERROR(EAGAIN)){
                continue;
            }
            is_close = true;
        }
    }
    return 0;
}
