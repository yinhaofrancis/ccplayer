//
//  Video.cpp
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#include "video.hpp"
#include "shader_import.h"
using namespace cc;

void video_display::load_program() {
    if(m_program_obj == nullptr){
        m_program_obj = new program(video_vertex_shader, video_fragment_shader);
    }
}

void video_display::load_vertex() {
    if(m_vertex_obj == nullptr){
        float v[8 * 6] = {
            -1,  1,  -2, 1    ,0,0,
            -1, -1,  -2, 1    ,0,1,
            1,  1,  -2, 1    ,1,0,
            1, -1,  -2, 1    ,1,1,
            
        };
        uint16_t vi[] = {
            0,1,3,3,2,0,
        };
        
        m_vertex_obj = new vertex(v, sizeof(v), 6 * sizeof(float));
        m_vertex_obj->load_element(vi, sizeof(vi));
        m_vertex_obj->layout(0, 4, 6, 0);
        m_vertex_obj->layout(1, 2, 6, 4);
        m_vertex_obj->commit();
    }
}

video_display::video_display(){
    m_vertex_obj = nullptr;
}
float& video_display::gamma(){
    return m_gamma;
}
video_display::~video_display(){
    if(m_program_obj != nullptr){
        m_program_obj->close();
        delete m_program_obj;
    }
    
    if(m_vertex_obj != nullptr){
        m_vertex_obj->close();
        delete m_vertex_obj;
    }
    tex.close();
    tex2.close();
    tex3.close();
}

texture video_display::texture_build(AVFrame * frame,int index){
    
    if(index == 1){
        return texture(frame->data[index], frame->width / 2,frame->height / 2 ,frame->linesize[index],GL_LUMINANCE,GL_LUMINANCE,GL_UNSIGNED_BYTE,GL_LINEAR,GL_CLAMP_TO_EDGE);;
    }
    if(index == 2){
        return texture(frame->data[index], frame->width / 2,frame->height / 2,frame->linesize[index],GL_LUMINANCE,GL_LUMINANCE,GL_UNSIGNED_BYTE,GL_LINEAR,GL_CLAMP_TO_EDGE);;
    }else{
        return texture(frame->data[index], frame->width,frame->height,frame->linesize[index],GL_LUMINANCE,GL_LUMINANCE,GL_UNSIGNED_BYTE,GL_LINEAR,GL_CLAMP_TO_EDGE);;
    }
}

void video_display::loadTexture(AVFrame *frame) {
    tex.close();
    tex2.close();
    tex3.close();
    if(frame->width > frame->height){
        frame_w = m_screen_w * 1.0f;
        frame_h = frame->height * m_screen_w / (frame->width * 1.0f);
    }else{
        frame_h = m_screen_h * 1.0f;
        frame_w = frame->width * m_screen_h / (frame->height * 1.0f);
    }
   
    tex = this->texture_build(frame, 0);
    tex2 = this->texture_build(frame, 1);
    tex3 = this->texture_build(frame, 2);
}

void video_display::render(AVFrame* frame){

    if(frame != nullptr && frame->width > 0 && frame->height > 0){
        loadTexture(frame);
    }
    
    if(frame_w == 0 || frame_h == 0 || m_screen_w == 0 || m_screen_h == 0){
        return;
    }
    load_program();
    load_vertex();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glViewport(0, 0, m_screen_w, m_screen_h);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto pro_mat = glm::ortho(-m_screen_w / 1.0f, m_screen_w / 1.0f, -m_screen_h / 1.0f, m_screen_h / 1.0f, 1.f, 100.f);
    auto mat1 = glm::scale(glm::mat4(1.0f), glm::vec3(frame_w,frame_h,1));
    this-> m_program_obj->bind();
    this-> m_program_obj->bindMatrix<4>(glm::value_ptr(mat1), "matrix");
    this-> m_program_obj->bindMatrix<4>(glm::value_ptr(pro_mat), "projection_matrix");
   
    this-> m_program_obj->bindTexture2D<0>(tex.texture_value(), "s_Y");
    this-> m_program_obj->bindTexture2D<1>(tex2.texture_value(), "s_U");
    this-> m_program_obj->bindTexture2D<2>(tex3.texture_value(), "s_V");
    this-> m_program_obj->bindValue(m_gamma, "v_gamma");
    
    this->m_vertex_obj->draw(GL_TRIANGLES);
}
