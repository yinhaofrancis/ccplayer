//
//  player.hpp
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#ifndef player_hpp
#define player_hpp


#include "../util/cc_util.hpp"
#include "../util/container.h"
#include "format.hpp"
#include "../render/audio.hpp"
#include "../util/type.h"


namespace cc {


class player{
    
public:
    
    player(const char * localpath);
    
    ~player();
    
    void read_packet(runner<player,true>&);
    
    
    
    void swap_frame(AVFrame *dframe, AVFrame *frame);
    
    
    
    void decode_video(runner<player,true>&);
    
    void decode_audio(runner<player,true>&);
    
    void seek_video_run(runner<player,true>& r);
    
    void play();
    
    void pause();
    
    void seek_to(double percent);
    
    const int MAX_AUDIO_COUNT = 2200;
    
    const int MAX_VIDEO_COUNT = 1800;
    
    const int MAX_AUDIO_DISPLAY_COUNT = 2;
    
    AVFrame* get_current_frame();
    
    player_state state();
    
    void rate(double rate);
    
    std::function<void(double,double)>& time_callback();
    
private:
    
    double video_frame_delay(AVFrame *frame);
    
    std::function<void(double,double)> m_time_callback = [](auto a,auto b) {};
    
    void clear_read_queue();
    
    void start_thread();
    
    bool is_close = false;
    
    bool is_read_end = false;
    
    double  m_rate = 1;
    
    player_state m_state = player_state_ending;
    
    format m_format;
    
    queue<AVPacket*> m_queue_video_packet;
    
    queue<AVPacket*> m_queue_audio_packet;
    

    audio_player m_audio_player;
    
    std::atomic<AVFrame*> m_video_frame;
    
    double current_audio_timestamp = 0;
    
    double current_audio_duration = 0;
    
    int64_t current_video_pts = -1;
    
    std::atomic<double> seek_current = 0;
    
    std::atomic<double> seek_duration = 0;
    
    runner<player,true>* read_thread;
    
    runner<player,true>* seek_thread;
    
    runner<player,true>* decode_video_thread;
    
    runner<player,true>* decode_audio_thread;
    
};







};

#endif /* player_hpp */
