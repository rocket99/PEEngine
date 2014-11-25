#version 300 es
layout (location=0) in mediump vec3 a_point;

uniform mediump vec3 u_space;
uniform mediump mat4 u_sysMat;
void main()
{
    gl_Position = u_sysMat * vec4(a_point/u_space, 1.0);
}