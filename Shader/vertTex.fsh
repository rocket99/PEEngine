#version 300 es

in mediump vec2 v_texCoord;

layout (location=0) out mediump vec4 frag_color;

uniform sampler2D u_texture;
uniform mediump vec4 u_color;

void main(){
    frag_color = texture(u_texture, v_texCoord) + u_color;
}

