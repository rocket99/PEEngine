#version 420

layout(location=0) in vec3 a_point;
layout(location=1) in vec4 a_color;

out vec4 v_color;

uniform vec3 u_position;
uniform vec3 u_space;

void main()
{
	gl_Position.xyz = (a_point+u_position)/u_space;
	gl_Position.w = 1.0;
	v_color = a_color;
}
