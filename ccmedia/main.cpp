#include "core/encoder/writer.hpp"
#include "core/player/format.hpp"


void test();
int main()
{

    cc::global_prepare();
    cc::writer w(
        "/Users/haoyin/Documents/gam.mp4"
    );
    w.transform("/Users/haoyin/Documents/mda-pivig2puqkxms0rb.mp4");

    int i;
    std::cin>>i;
    return 0;
}
void test()
{
    AVFrame *frame = av_frame_alloc();
    AVPacket *packet = av_packet_alloc();
    AVPacket *packet2 = av_packet_alloc();
    cc::global_prepare();
    cc::format m_format("/Users/haoyin/Documents/gamesci_2022PV03.mp4");

    cc::encoder m(1280, 720);
    cc::encoder au(AV_SAMPLE_FMT_FLTP, 2, 22050);
    m.open();
    au.open();
    m_format.load_codec();
    bool is_close = false;
    while (!is_close)
    {
        try
        {
            m_format.read(packet);
            if (packet->stream_index == m_format.video_index())
            {
                m_format.decode_video_core(frame, packet);
                std::cout << av_get_picture_type_char(frame->pict_type) << std::endl;
                m.encode(frame, packet2);
                std::cout << packet2->pts << std::endl;
            }
            if (packet->stream_index == m_format.audio_index())
            {
                m_format.decode_audio_core(frame, packet);
                au.encode(frame, packet2);
                std::cout << "audio" << packet2->pts << std::endl;
            }
        }
        catch (cc::error e)
        {
            if (e.code == AVERROR(EAGAIN))
            {
                continue;
            }
            is_close = true;
        }
    }
}
