#version 300 es

layout (location=0) in mediump vec3 a_point;
layout (location=1) in mediump vec2 a_texCoord;
uniform mediump vec3 u_space;
uniform mediump mat4 u_sysMat;
uniform mediump mat4 u_modelViewProject;

out mediump vec2 v_texCoord;

void main(){
    gl_PointSize = 1.0;
    gl_Position = u_modelViewProject * u_sysMat * vec4(a_point/u_space, 1.0);
    v_texCoord = a_texCoord;
}

