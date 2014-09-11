#version 300 es

layout (location=0) in mediump vec3 a_point;

uniform mediump vec3 u_space;
uniform mediump mat4 u_sysMat;
uniform mediump mat4 u_modelViewProject;
out mediump float v_depth;
void main(){
    gl_PointSize = 1.0;
    gl_Position = u_modelViewProject * u_sysMat * vec4(a_point/u_space, 1.0);
    v_depth = 0.5*gl_Position.z+0.5;
}

