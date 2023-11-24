

#ifndef WHITER_H
#define WHITER_H

#include "encoder.hpp"
#include "../util/cc_util.hpp"

namespace cc
{
    class writer
    {
    public:
        writer(const char* path);
        ~writer();
    private:
        AVFormatContext *m_format_ctx;
        encoder m_video_encoder;
        encoder m_audio_encoder;

    };
};

#endif