

#ifndef WHITER_H
#define WHITER_H

#include "encoder.hpp"
#include "../util/cc_util.hpp"
#include "../player/format.hpp"
#include "../util/container.h"

namespace cc
{
    struct writer_transform_task;

    class writer
    {
    public:
        writer(const char *path);
        ~writer();
        void transform(const char *from);

    private:
        AVFormatContext *m_format_ctx;
        encoder m_video_encoder;
        encoder m_audio_encoder;

        runner<writer, true> *transform_runner;

        void transform_run(runner<writer, true>& r,const char *from);
    };
};

#endif