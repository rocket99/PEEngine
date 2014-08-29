#version 300 es
in mediump vec3 v_point;
in mediump vec2 v_texCoord;
in mediump vec3 v_normal;

layout (location=0) out mediump vec4 frag_color;

uniform sampler2D u_texture;

void main(){
    frag_color = texture(u_texture, v_texCoord);
}


