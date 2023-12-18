#include "encoder.hpp"



using namespace cc;

encoder::encoder(AVCodecID codec_id,AVPixelFormat pixel_fmt, int width, int height,int gop,int max_b_frames,int fps)
{
    
    this->m_codec = avcodec_find_encoder(codec_id);
    if(this->m_codec == nullptr){
        throw(cc::error(
            "can't find codec id",0
        ));
    }
    this->m_codec_ctx = avcodec_alloc_context3(this->m_codec);
    this->m_codec_ctx->width = width;
    this->m_codec_ctx->height = height;
    this->m_codec_ctx->pix_fmt = pixel_fmt;
    this->m_codec_ctx->codec_id = codec_id;
    this->m_codec_ctx->gop_size = gop;
    this->m_codec_ctx->max_b_frames = max_b_frames;
    this->m_codec_ctx->time_base = (AVRational){1,fps};
}
encoder::encoder(AVCodecID codec_id,AVSampleFormat sample_fmt,int channel,int sample_rate){
    this->m_codec = avcodec_find_encoder(codec_id);
    if(this->m_codec == nullptr){
        throw(cc::error(
            "can't find codec id",0
        ));
    }
    this->m_codec_ctx = avcodec_alloc_context3(this->m_codec);
    this->m_codec_ctx->codec_id = codec_id;
    this->m_codec_ctx->sample_fmt = sample_fmt;
    this->m_codec_ctx->channels = channel;
    this->m_codec_ctx->sample_rate = sample_rate;
    this->m_codec_ctx->channel_layout = av_get_default_channel_layout(channel);
    this->m_codec_ctx->time_base = (AVRational){1,sample_rate};
}
encoder::encoder(encoder &n)
{
    this->m_codec_ctx = n.m_codec_ctx;
    n.m_codec_ctx = nullptr;
    this->m_codec = n.m_codec;
    n.m_codec = nullptr;
    this->m_stream = n.m_stream;
    n.m_stream = nullptr;
}
 encoder::encoder(AVSampleFormat sample_fmt,int channel,int sample_rate):encoder(AV_CODEC_ID_AAC,sample_fmt,channel,sample_rate){

 }
encoder::encoder(int width, int height):encoder(AV_CODEC_ID_H264,AV_PIX_FMT_YUV420P, width, height,40,20,30){

}

int &encoder::codec_flags()
{
    return this->m_codec_ctx->flags;
}


void encoder::open()
{
    int err = avcodec_open2(m_codec_ctx, m_codec, nullptr);
    if (err != 0)
    {
        throw cc::error(err);
    }
}
void encoder::encode(AVFrame *frame, AVPacket *packet)
{
    this->lock.lock();
    int err = avcodec_send_frame(m_codec_ctx, frame);
    this->lock.unlock();
    if (err != 0)
    {
        throw cc::error(err);
    }
    this->lock.lock();
    err = avcodec_receive_packet(m_codec_ctx, packet);
    this->lock.unlock();
    if (err != 0)
    {
        throw cc::error(err);
    }
}
void encoder::close()
{
    int err = avcodec_close(m_codec_ctx);
    if (err != 0)
    {
        throw cc::error(err);
    }
}
void encoder::load_stream(AVFormatContext *format_ctx)
{
    AVStream *stream = avformat_new_stream(format_ctx, m_codec);
    if (stream == nullptr)
    {
        throw cc::error("create avstream fail", 0);
    }

    stream->codecpar->codec_tag = 0;
    avcodec_parameters_from_context(stream->codecpar, m_codec_ctx);
    this->m_stream = stream;
}

AVStream & encoder::stream(){
    return *m_stream;
}

encoder::~encoder()
{
    close();
    avcodec_free_context(&this->m_codec_ctx);
}
