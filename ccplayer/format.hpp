//
//  format.hpp
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#ifndef format_hpp
#define format_hpp


#include "container.h"
#include "cc_util.hpp"

namespace cc {

struct error{
    std::string msg;
    int code;
    
    error(std::string& msg,int code):msg(msg),code(code){
        std::cout << msg << std::endl;
    }
    
    error(std::string&& msg,int code):msg(msg),code(code){
        std::cout << msg << std::endl;
    }
    
    error(int err) {
        char buff [512];
        av_strerror(err, buff, 512);
        std::string cppmsg = msg;
        code = err;
        msg = cppmsg;
        std::cout << msg << std::endl;
    }
};


class format{
    
    AVFormatContext             *m_ctx = nullptr;
    
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
    
    ~format();
    
    AVRational& video_timebase();
    
    AVRational& audio_timebase();
    
    double video_timestamp_transform(int64_t pts);
    
    double audio_timestamp_transform(int64_t pts);
    
    int64_t video_duration(){
        return m_ctx->streams[this->m_video_index]->duration;
    }
    
    int64_t audio_duration(){
        return m_ctx->streams[this->m_audio_index]->duration;
    }
    int64_t fps(){
        auto ass = m_ctx->streams[this->m_video_index]->avg_frame_rate;
        if(ass.num == 0){
            return 0;
        }
        return ass.num / ass.den;
    }
    void flush();
    void seek(double ts,double max,bool grow);
    
    AVPacket* read();
    
    friend class player;
    
};

};
#endif /* format_hpp */
