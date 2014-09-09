#version 300 es

//in mediump vec2 v_texCoord;

layout (location=0) out mediump vec4 frag_color;

//uniform sampler2D u_texture;
//uniform mediump vec4 u_color;

void main(){
    frag_color = vec4(0.75, 0.75, 0.75, 1.0) /*texture(u_texture, v_texCoord)*/;
}

