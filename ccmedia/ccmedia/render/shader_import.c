#include "shader_import.h"




const char * video_vertex_shader = shader_code(#version 300 es

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vUV;

uniform mat4 projection_matrix;
uniform mat4 matrix;

out vec2 s_uv;

void main(){
    gl_Position = projection_matrix * matrix  * vPosition;
    s_uv = vUV;
}
                                               );

const char * video_fragment_shader = shader_code(#version 300 es
 precision highp float;
                                                 
 uniform sampler2D   s_Y;
 uniform sampler2D   s_U;
 uniform sampler2D   s_V;
 uniform float       v_gamma;

 in vec2 s_uv;

 layout (location = 0) out vec4 fragColor;

 void main(){
    float y =   texture(s_Y,s_uv).x;
    float u =   texture(s_U,s_uv).x - 0.5;
    float v =   texture(s_V,s_uv).x - 0.5;
    float r =   pow(y + 1.403 * v,1.0 / v_gamma);
    float g =   pow(y - 0.344 * u - 0.714 * v,1.0 / v_gamma);
    float b =   pow(y + 1.770 * u,1.0 / v_gamma);
    fragColor = vec4(r,g,b,1.0);
 }

                                                 );
