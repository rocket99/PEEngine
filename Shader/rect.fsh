#version 300 es

in mediump vec2 v_texCoord;

uniform sampler2D pic;
uniform mediump vec4 u_color;

layout (location = 0) out mediump vec4 frag_color;

void main()
{
//    mediump vec4 color = texture(pic, v_texCoord);
    frag_color = vec4(1.0, 0.0, 0.0, 1.0) + u_color;
}

