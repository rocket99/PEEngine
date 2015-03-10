#version 420

layout(location=0) in vec3 a_point;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texCoord;

out vec4 v_color;
out vec2 v_texCoord;

uniform vec3 u_space;
uniform vec3 u_offset;

void main(){
	gl_Position = vec4((a_point+u_offset)/u_space, 1.0);
	v_texCoord = a_texCoord;
	v_color = a_color;
}


