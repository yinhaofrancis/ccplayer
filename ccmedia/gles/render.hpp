//
//  Render.hpp
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#ifndef Render_hpp
#define Render_hpp

#include "cc_util.hpp"

namespace cc{

struct texture_buffer{
    void* buffer;
    int w,h;
    texture_buffer(void* buffer, int w, int h){
        this->buffer = buffer;
        this->w = w;
        this->h = h;
    }
    texture_buffer(const texture_buffer& old){
        this->w = old.w;
        this->h = old.h;
        this->buffer = old.buffer;
    }
};


class uniform{
    GLuint _location;
public:
    
    
    uniform(GLuint location):_location(location){};
    
    template<int D>
    std::enable_if_t<(D == 4 || D == 3), void>
    bindMatrix(float* buffer){
        if(D == 4){
            glUniformMatrix4fv(_location, 1, GL_FALSE, buffer);
        }
        if(D == 3){
            glUniformMatrix3fv(_location, 1, GL_FALSE, buffer);
        }
    }
    
    template<int D>
    std::enable_if_t<(D <= 4 && D > 1), void>
    bindVector(float buffer [D]){
        if(D == 4){
            glUniform4f(_location, buffer[0], buffer[1], buffer[2], buffer[3]);
        }
        if(D == 3){
            glUniform3f(_location, buffer[0], buffer[1], buffer[2]);
        }
        if(D == 2){
            glUniform2f(_location, buffer[0], buffer[1]);
        }
        if(D == 1){
            glUniform1f(_location, buffer[0]);
        }
    }
    template<int D>
    std::enable_if_t<(D <= 4 && D > 1), void>
    bindVector(int buffer [D]){
        if(D == 4){
            glUniform4i(_location, buffer[0], buffer[1], buffer[2], buffer[3]);
        }
        if(D == 3){
            glUniform3i(_location, buffer[0], buffer[1], buffer[2]);
        }
        if(D == 2){
            glUniform2i(_location, buffer[0], buffer[1]);
        }
        if(D == 1){
            glUniform1i(_location, buffer[0]);
        }
    }
    template<int D>
    std::enable_if_t<(D == 1), void>
    bindValue(float value){
        glUniform1f(_location, value);
    }
    template<int D>
    std::enable_if_t<(D == 1), void>
    bindValue(int value){
        glUniform1i(_location, value);
    }
    template<int D>
    std::enable_if_t<(D < 32), void>
    bindTexture2D(GLuint buffer){
        glUniform1i(_location, D);
        glActiveTexture(GL_TEXTURE0 + D);
        glBindTexture(GL_TEXTURE_2D, buffer);
    }
};



class shader{
    GLuint _handle;
public:
    shader(std::string& code,GLenum type);
    shader(const char * code,GLenum type);
    shader(const shader&);
    ~shader();
    bool check();
    static shader shader_from_file(const char * path,GLenum type);
    friend class program;
};
class program{
    GLuint _handle;
    
public:
    program(std::string& vertex,std::string& fragment);
    program(const char * vertex,const char * fragment);
    program(shader& vertex,shader& fragment);
    program(shader&& vertex,shader&& fragment);
    program(const program&);
    program(GLuint handle);
    void close();
    bool check();
    void bind() const;
    void unbind() const;
    program dup() const;
    GLuint operator [](const char * name);
    
    template<int D>
    void bindMatrix(float *v,const char *name){
        uniform((*this)[name]).bindMatrix<D>(v);
    }
    template<int D,typename T>
    void bindVector(T v[D],const char *name){
        uniform((*this)[name]).bindVector<D>(v);
    }
    template<typename T>
    void bindValue(T v,const char *name){
        uniform((*this)[name]).bindValue<1>(v);
    }
    
    template<int D>
    void bindTexture2D(GLint v,const char *name){
        uniform((*this)[name]).bindTexture2D<D>(v);
    }
    static void free_compiler();
    friend class simple_texture_object;
    friend class object;
};

class vertex{
    
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    uint32_t vertex_count;
    uint32_t vertex_size;
    uint32_t element_count;
    
public:
    vertex(const float* vertex_buffer,uint32_t bufferSize,uint32_t vertex_size){
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        this->vertex_size = vertex_size;
        vertex_count = bufferSize / vertex_size;
        glBufferData(GL_ARRAY_BUFFER, bufferSize, vertex_buffer, GL_STATIC_DRAW);
    }
    
    vertex(vertex& vertex):vao(vertex.vao),vbo(vertex.vbo),ebo(vertex.ebo),vertex_count(vertex.vertex_count),vertex_size(vertex.vertex_size),element_count(vertex.element_count){
    }
    vertex(vertex&& vertex):vao(vertex.vao),vbo(vertex.vbo),ebo(vertex.ebo),vertex_count(vertex.vertex_count),vertex_size(vertex.vertex_size),element_count(vertex.element_count){
        vertex.vao = vertex.vbo = vertex.ebo = 0;
    }
    vertex & operator =(vertex&& vertex){
        this->vao = vertex.vao;
        this->vbo = vertex.vbo;
        this->ebo = vertex.ebo;
        this->vertex_count = vertex.vertex_count;
        this->vertex_size = vertex.vertex_size;
        this->element_count = vertex.element_count;
        vertex.vao = vertex.vbo = vertex.ebo = 0;
        return *this;
    }
    vertex & operator =(vertex& vertex){
        this->vao = vertex.vao;
        this->vbo = vertex.vbo;
        this->ebo = vertex.ebo;
        this->vertex_count = vertex.vertex_count;
        this->vertex_size = vertex.vertex_size;
        this->element_count = vertex.element_count;
        return *this;
    }
    void layout(int index,int count,int component_count,int offset){
        glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, component_count * sizeof(float), (const void *)(offset * sizeof(float)));
        glEnableVertexAttribArray(index);
    }
    
    void load_element(const uint16_t* vertex_buffer,uint32_t bufferSize){
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        this->element_count = bufferSize / sizeof(uint16_t);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, vertex_buffer, GL_STATIC_DRAW);
    }
    void draw(GLenum mode){
        glBindVertexArray(vao);
        if (ebo){
            glDrawElements(mode, this->element_count, GL_UNSIGNED_SHORT, 0);
        }else{
            glDrawArrays(mode, 0, this->vertex_count);
        }
        glBindVertexArray(0);
    }
    void commit(){
        glBindVertexArray(0);
    }
    void close(){
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
};

class texture{
    GLuint _texture = 0;
    int _w = 0,_h = 0;
public:
    texture(){}
    texture(const void *buffer,
            int w, int h,
            GLenum filter,
            GLenum wrap):texture(buffer,w,h,0,GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE,filter,wrap){
    }
    texture(const void *buffer,
            int w, int h,int linesize,
            GLint internalFormat,
            GLint format,
            GLint type,
            GLenum filter,
            GLenum wrap){
        _w = w;
        _h = h;
        GLuint texture;
        glGenTextures(1, &texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glPixelStorei(GL_UNPACK_ROW_LENGTH,fmax(w,linesize));
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, type, buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glBindTexture(GL_TEXTURE_2D, 0);
        this->_texture = texture;
    }
    
    
    texture(texture_buffer &buffer,
            GLenum filter,
            GLenum wrap):texture(buffer.buffer,buffer.w,buffer.h,filter,wrap){}
    
    texture(GLuint texture,
            int w,
            int h):_texture(texture),_w(w),_h(h){}
    
    texture(const texture& c):_texture(c._texture),_w(c._w),_h(c._h) {}
    
    texture& operator =(texture& c){
        this->_texture = c._texture;
        return (*this);
    }
    
    texture(texture&& c):_texture(c._texture),_w(c._w),_h(c._h) {
        c._texture = 0;
    }
    
    void bind(){
        glBindTexture(GL_TEXTURE_2D, _texture);
    }
    void unbind(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    texture& operator =(texture&& c){
        this->_texture = c._texture;
        c._texture = 0;
        return (*this);
    }
    
    void modify(int x, int y,int w, int h,const uint8_t *buffer){
        glBindTexture(GL_TEXTURE_2D, _texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 32);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 32);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    void close(){
        glDeleteTextures(1, &_texture);
    }
    GLuint texture_value(){
        return _texture;
    }
    friend class object;
    friend class simple_texture_object;
};



class frame_buffer{
    GLuint _frame_buffer;
    GLuint _render_buffer[2];
    GLuint _texture[2];
    bool hasStencil;
    GLuint width;
    GLuint height;
public:
    bool layout_buffer(GLuint w, GLuint h,bool hasStencil) {
        if(w != width || h != height || hasStencil != this->hasStencil ){
            width = w;
            height = h;
            this->hasStencil = hasStencil;
            glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
            glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[0]);;
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _render_buffer[0]);
            glBindTexture(GL_TEXTURE_2D, _texture[0]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture[0], 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            if (hasStencil){
                glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[1]);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _render_buffer[1]);
                glBindTexture(GL_TEXTURE_2D, _texture[1]);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, w, h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _texture[1], 0);
                glBindTexture(GL_TEXTURE_2D,0);
            }else{
                glBindRenderbuffer(GL_RENDERBUFFER, _render_buffer[1]);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _render_buffer[1]);
                glBindTexture(GL_TEXTURE_2D, _texture[1]);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT,GL_UNSIGNED_INT, NULL);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _texture[1], 0);
                glBindTexture(GL_TEXTURE_2D,0);
            }
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return true;
        }
        return false;
    }
    
    frame_buffer(){
        glGenFramebuffers(1, &_frame_buffer);
        glGenRenderbuffers(2, _render_buffer);
        glGenTextures(2, _texture);
    }
    void close(){
        glDeleteFramebuffers(1, &_frame_buffer);
        glDeleteRenderbuffers(2, _render_buffer);
        glDeleteTextures(2, _texture);
    }

    GLuint render_buffer(){
        return _render_buffer[0];
    }
    void commit(){
        glBindFramebuffer(GL_FRAMEBUFFER, 1);
    }
    texture color_texture(){
        return texture(_texture[0],width,height);
    }
    GLuint color_texture_id(){
        return _texture[0];
    }
    texture depth_texture(){
        return texture(_texture[1],width,height);
    }
    GLuint color_render_buffer(){
        return _render_buffer[0];
    }
    GLuint depth_render_buffer(){
        return _render_buffer[1];
    }
    void load(){
        glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
    }
    void copy(GLenum attachment,GLuint framebuffer){
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _frame_buffer);
        glReadBuffer(attachment);
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }
    bool framebuffer_complete(){
        GLenum v = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if(v == GL_FRAMEBUFFER_COMPLETE){
            return true;
        }
        return false;
    }
};

};



#endif /* Render_hpp */
