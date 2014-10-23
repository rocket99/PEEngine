#version 300 es

layout (location =0) in mediump vec3 a_point;
layout (location =1) in mediump vec2 a_texCoord;

out mediump vec2 v_texCoord;
uniform mediump vec3 u_space;

void main()
{
    gl_PointSize = 2.0;
    gl_Position = vec4(a_point/u_space, 1.0);
    v_texCoord = a_texCoord;
}
