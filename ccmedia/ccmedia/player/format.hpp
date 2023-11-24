//
//  format.hpp
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#ifndef format_hpp
#define format_hpp


#include "../util/container.h"
#include "../util/cc_util.hpp"

namespace cc {


class format{
    
    AVFormatContext             *m_format_ctx = nullptr;
    
    std::string                 m_path;             /*路径*/
    
    std::atomic_bool            m_flag_eof = false;
    
    int                         m_audio_index = -1;      /*音频索引*/
    
    int                         m_video_index = -1;    /*视频索引*/
    
    
    struct codec{
        
        AVCodec*                            p_codec = nullptr;
        
        AVCodecContext                      *p_ctx = nullptr;
        
        AVCodecParameters                   *p_param = nullptr;
        
        std::mutex                          m_mutex;
        
    public:
        int width(){    return p_ctx->width;     }
        
        int height(){   return p_ctx->height;    }
        
        codec ();
        
        ~codec ();
        
        void config(AVCodecID ,AVCodecParameters *);
        
    };
    
    codec                       m_video_codec;
    
    codec                       m_audio_codec;
    
    std::mutex                  read_lock;
    
public:
    
    int audio_index() { return m_audio_index; }
    
    int video_index() { return m_video_index; }
    
    format(const char *localPath);

    void load_codec();

    ~format();

    AVRational &video_timebase();

    AVRational &audio_timebase();

    double video_timestamp_transform(int64_t pts);
    
    double audio_timestamp_transform(int64_t pts);
    
    int64_t video_duration(){
        return m_format_ctx->streams[this->m_video_index]->duration;
    }
    
    int64_t audio_duration(){
        return m_format_ctx->streams[this->m_audio_index]->duration;
    }
    int64_t fps(){
        auto ass = m_format_ctx->streams[this->m_video_index]->avg_frame_rate;
        if(ass.num == 0){
            return 0;
        }
        return ass.num / ass.den;
    }
    void flush();
    void seek(double ts,double max,bool grow);
    void decode_video_core(AVFrame *frame, AVPacket *packet);
    
    void decode_audio_core(AVFrame *frame, AVPacket *packet);
    AVPacket* read();
    
    friend class player;
    
};

};
#endif /* format_hpp */
