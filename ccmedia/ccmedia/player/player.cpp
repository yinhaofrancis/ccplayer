//
//  player.cpp
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#include "player.hpp"

using namespace cc;


player::player(const char * localpath):m_format(localpath){
    m_format.load_codec();
    if(m_format.m_audio_codec.p_ctx != nullptr){
        m_audio_player.config(*m_format.m_audio_codec.p_ctx);
    }
}

void player::clear_read_queue() {
    this->m_queue_audio_packet.lock_function([&](auto& t){
        for (auto v : t) {
            av_packet_free(&v);
        }
        t.clear();
    });
    this->m_queue_video_packet.lock_function([&](auto& t){
        for (auto v : t) {
            av_packet_free(&v);
        }
        t.clear();
    });
}

player::~player(){
    is_close = true;
    delete read_thread;
    
    delete decode_video_thread;
    
    delete decode_audio_thread;
    
    delete seek_thread;
    this->m_time_callback = nullptr;
    clear_read_queue();
}
void player::read_packet(runner<player,true>& r){

    while (!r.is_close()) {
        if(this->is_close){
            r.close();
        }
        if(this->state() == player_state_paused){
            r.sleep_millisec(50);
            continue;
        }
        if(this->is_read_end){
            r.sleep_millisec(250);
            is_read_end = false;
            continue;
        }
        if(m_queue_audio_packet.size() > MAX_AUDIO_COUNT && m_queue_video_packet.size() > MAX_VIDEO_COUNT){
            r.sleep_millisec(1);
            continue;
        }
        try {
            
            auto packet = m_format.read();
            if(packet->stream_index == m_format.video_index()){
                m_queue_video_packet.enqueue(packet);
            }else if(packet->stream_index == m_format.audio_index()){
                m_queue_audio_packet.enqueue(packet);
            }else{
                av_packet_free(&packet);
            }
        } catch (error e) {
            if(e.code == AVERROR_EOF){
                is_read_end = true;
            }else{
                printf("error    %s",e.msg.c_str());
            }
            r.sleep_millisec(200);
            
        }
        
    }
}



void player::swap_frame(AVFrame *dframe, AVFrame *frame) {
    av_frame_unref(dframe);
    av_frame_ref(dframe, frame);
    this->current_video_pts = dframe->pts;
    this->m_video_frame = dframe;
    av_frame_unref(frame);
}

void player::seek_video_run(runner<player,true>& r){
 
    while (!r.is_close()){
        if(this->m_state != player_state_seeking){
            r.sleep_millisec(300);
            continue;
        }
        if(this->seek_current > 0){;
            clear_read_queue();
            this->current_audio_duration = 0;
            this->current_audio_timestamp = 0;
            this->current_video_pts = 0;
            
            m_format.seek(this->seek_current, this->seek_duration,true);
            
            r.sleep_millisec(16);
        }
        r.sleep_millisec(16);
    }
}

double player::video_frame_delay(AVFrame *frame) {
    if(m_format.m_audio_codec.p_ctx == nullptr){
        return m_format.video_timestamp_transform(frame->pkt_duration) * 1000 / m_rate;
    }else{
        double current_video_timestamp = m_format.video_timestamp_transform(frame->pts) * 1000;
        double delta =  current_video_timestamp - current_audio_timestamp + current_audio_duration; // 时间戳对比
        delta = delta / m_rate;
        return delta;
    }
}

void player::decode_video(runner<player,true>& r){
    auto frame = av_frame_alloc(); //双缓冲
    auto dframe = av_frame_alloc();
    while (!r.is_close()) {
        if(this->is_close){
            r.close();
        }
        if(m_state == player_state_paused){
            r.sleep_millisec(50);
            continue;
        }
        if(m_queue_video_packet.size() == 0){
            r.sleep_millisec(12);
            continue;
        }
        auto packet = m_queue_video_packet.dequeue();
        try {
            m_format.decode_video_core(frame, packet);
            av_packet_free(&packet);
        } catch (error e) {
            av_packet_free(&packet);
            r.sleep_millisec(1);
            continue;
        }

        if(m_state == player_state_seeking) {
            m_state = player_state_paused;
            swap_frame(dframe, frame);
        }else{
            double delta = video_frame_delay(frame);
            std::cout << delta << std::endl;
            if(delta > 10 && delta < 1000){
                r.sleep_millisec(delta);
                swap_frame(dframe, frame);
            }else {
                swap_frame(dframe, frame);
            }
            
        }
        
    }
    this->m_video_frame = nullptr;
    av_frame_free(&frame);
    av_frame_free(&dframe);
}

void player::decode_audio(runner<player,true>& r){
    auto frame = av_frame_alloc();

    while (!r.is_close()) {
        if(this->is_close){
            r.close();
            continue;
        }
        if(this->m_state == player_state_seeking){
            r.sleep_millisec(50);
            continue;;
        }
        if(this->m_state == player_state_paused){
            r.sleep_millisec(50);
            continue;;
        }
        if(m_queue_audio_packet.size() == 0){
            r.sleep_millisec(12);
            continue;;
        }
        auto packet = m_queue_audio_packet.dequeue();
        
        try {
            m_format.decode_audio_core(frame, packet);
            av_packet_free(&packet);
        } catch (error e) {
            av_packet_free(&packet);
            r.sleep_millisec(1);
            continue;
        }
        while(m_audio_player.buffer_count() > ceil(MAX_AUDIO_DISPLAY_COUNT * this->m_rate)){
            m_audio_player.dequeue_buffer();
            r.sleep_millisec(8);
        }
       
        current_audio_timestamp = m_format.audio_timestamp_transform(frame->pts) * 1000;
        
        current_audio_duration = m_format.audio_timestamp_transform(frame->pkt_duration) * 1000;
        
        auto duration = m_format.audio_timestamp_transform(m_format.audio_duration()) * 1000;
        
        if(state() == player_state_playing){
            if(m_time_callback != nullptr){
                this->m_time_callback(current_audio_timestamp,duration);
            }
        }
        
        m_audio_player.render(frame);
        av_frame_unref(frame);
    }
    av_frame_free(&frame);
}
player_state player::state(){
    return m_state;
}
void player::rate(double rate){
    m_audio_player.rate(rate);
    this->m_rate = rate;
}
void player::start_thread(){
    
    this->read_thread = new runner<player,true>([this](auto& r){
        this->read_packet(r);
    });
    this->decode_video_thread = new runner<player,true>([this](auto& r){
        this->decode_video(r);
    });
    this->decode_audio_thread = new runner<player,true>([this](auto& r){
        this->decode_audio(r);
    });
    this->seek_thread = new runner<player, true>([this] (auto & t) {
        this->seek_video_run(t);
    });
}

AVFrame * player::get_current_frame(){
    if(current_video_pts < 0){
        return nullptr;
    }
    if(m_video_frame == nullptr){
        return nullptr;
    }
//    auto frame = av_frame_alloc();
//    av_frame_ref(frame, m_video_frame);
    AVFrame* m = m_video_frame;
    m_video_frame = nullptr;
    
    return m;
}

void player::play(){
    this->m_state = player_state_playing;
    if(read_thread == nullptr){
        start_thread();
    }
}

void player::pause(){
    this->m_state = player_state_paused;
}
std::function<void(double,double)>& player::time_callback(){
    return m_time_callback;
}

void player::seek_to(double percent){
    this->m_state = player_state_seeking;
    is_read_end = false;
    double during = m_format.video_timestamp_transform(m_format.video_duration());
    double current = percent * during;
    this->seek_current = current;
    this->seek_duration = during;
     
}

