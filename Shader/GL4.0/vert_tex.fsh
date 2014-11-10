#version 420

in vec2 v_texCoord;
uniform sampler2D u_texture;

layout(location=0) out vec4 frag_color;

void main(){
	frag_color = texture(u_texture, v_texCoord);
}
