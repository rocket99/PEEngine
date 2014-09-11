#version 300 es

layout (location =0) in mediump vec3 a_point;
layout (location =1) in mediump vec2 a_texCoord;

out mediump vec2 v_texCoord;

void main()
{
    gl_Position = vec4(a_point, 1.0);
    v_texCoord = a_texCoord;
}