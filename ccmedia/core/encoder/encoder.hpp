
#ifndef ENCODER_H
#define ENCODER_H

#include "../util/cc_util.hpp"
#include "../util/container.h"

namespace cc
{
    enum encoder_type{
        video,audio
    };
    class encoder
    {
    public:
        encoder(AVCodecID codec_id,AVPixelFormat pixel_fmt, int width, int height,int gop,int max_b_frames,int fps);
        encoder(AVCodecID codec_id,AVSampleFormat sample_fmt,int channel,int sample_rate);
        encoder(encoder &);
        encoder(AVSampleFormat sample_fmt,int channel,int sample_rate);
        encoder(int width, int height);
        ~encoder();

        int &codec_flags();
        int &bit_rate();

        AVStream &stream();

        void open();
        void close();
        void load_stream(AVFormatContext *m_format_ctx);
        void encode(AVFrame *frame, AVPacket *packet);

    private:

        AVCodecContext *m_codec_ctx = nullptr;

        AVStream *m_stream = nullptr;

        AVCodec *m_codec = nullptr;

        int m_bitRate = 512000;

        std::mutex lock;
    };

};

#endif