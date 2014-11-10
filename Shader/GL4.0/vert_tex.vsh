#version 420

layout (location=0) in vec3 a_point;
layout (location=1) in vec2 a_texCoord;
layout (location=2) in vec3 a_normal;

uniform vec3 u_space;
uniform mat4 u_sysMat;
uniform mat4 u_modelViewProject;
out vec2 v_texCoord;

void main()
{
	gl_Position = u_modelViewProject*u_sysMat*vec4(a_point/u_space, 1.0);
	v_texCoord = a_texCoord;
}
