//
//  Video.hpp
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#ifndef Video_hpp
#define Video_hpp

#include "../util/cc_util.hpp"
#include "render.hpp"

namespace cc {

class video_display{
    
    vertex *m_vertex_obj;
    
    program *m_program_obj;
    
    frame_buffer* buffer;
    
    int m_screen_w;
    
    int m_screen_h;
    
    float frame_w;
    
    float frame_h;
    
    float m_gamma = 0.75;
    
    texture tex;
    
    texture tex2;
    
    texture tex3;
    
    texture texture_build(AVFrame * frame,int index);
    
    void load_vertex();
    
    void load_program();
    
    void loadTexture(AVFrame *frame);
    
public:
    void setScreen(int w,int h){
        m_screen_w = w;
        m_screen_h = h;
    }
    void render(AVFrame* frame);
    
    video_display();
    
    ~video_display();
    
    float& gamma();
};

};


#endif /* RenderVideo_hpp */
