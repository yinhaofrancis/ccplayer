//
//  Render.cpp
//  CCRender
//
//  Created by wenyang on 2023/11/20.
//

#include "render.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace cc;

shader::shader(std::string& path,GLenum type):shader(path.c_str(), type){}

shader shader::shader_from_file(const char * path,GLenum type){
    std::ifstream file;
    file.open(path);
    std::string code;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            code += (line + " ");
        }
        file.close();
    }
    return shader(code, type);
}
shader::shader(const char * c_code ,GLenum type){
    std::string code = c_code;
    auto shader = glCreateShader(type);
    GLsizei c = (GLsizei)code.size();
    const char * source = code.c_str();
    glShaderSource(shader, 1, &source, &c);
    glCompileShader(shader);
    this->_handle = shader;
    if (!check()){
        throw "create shader fail";
    }
}

bool shader::check(){
    GLint compile = 0;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &compile);
    if(!compile){
        GLint loglen = 0;
        glGetShaderiv(_handle, GL_INFO_LOG_LENGTH, &loglen);
        if(loglen > 1){
            char * logs = new char[loglen];
            glGetShaderInfoLog(_handle, loglen, &loglen, logs);
            auto msg = std::string(logs);
            std::cout <<msg << std::endl;
            delete [] logs;
            glDeleteShader(_handle);
            return false;
        }
    }
    return true;
}
shader::shader(const shader& n){
    this->_handle = n._handle;
}

shader::~shader(){
    glDeleteShader(_handle);
}

program program::dup() const{
    uint8_t buffer[1024 * 1024];
    int size = 0;
    GLenum bf;
    glGetProgramBinary(this->_handle, 1024 *1024, &size, &bf, buffer);
    GLuint prog = glCreateProgram();
    glProgramBinary(prog, bf, buffer, size);
    return program(prog);
}
program::program(GLuint handle):_handle(handle){}

program::program(shader&& vertex,shader&& fragment){
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex._handle);
    glAttachShader(program, fragment._handle);
    glLinkProgram(program);
    _handle = program;
    if (!check()){
        throw "create shader program fail";
    }
}
program::program(std::string& vertex,std::string& fragment):program(shader(vertex, GL_VERTEX_SHADER),shader(fragment, GL_FRAGMENT_SHADER)){}
program::program(const char * vertex,const char * fragment):program(shader(vertex, GL_VERTEX_SHADER),shader(fragment, GL_FRAGMENT_SHADER)){}
void program::close(){
    glDeleteProgram(_handle);
}
program::program(const program& p){
    _handle = p._handle;
}

void program::bind() const{
    glUseProgram(_handle);
}
void program::unbind() const{
    glUseProgram(0);
}

bool program::check(){
    GLint linked;
    glGetProgramiv(_handle, GL_LINK_STATUS, &linked);
    if(!linked){
        GLint loglen = 0;
        glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &loglen);
        if(loglen > 1){
            char * logs = new char[loglen];
            glGetProgramInfoLog(_handle, loglen, &loglen, logs);
            auto msg = std::string(logs);
            std::cout <<msg << std::endl;
            delete [] logs;
            glDeleteProgram(_handle);
            return false;
        }
    }
    return true;
}
void program::free_compiler(){
    glReleaseShaderCompiler();
}
GLuint program::operator [] (const char * name){
    return glGetUniformLocation(_handle, name);
}


