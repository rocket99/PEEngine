#version 420

layout(location=0) in vec3 a_point;
layout(location=1) in vec2 a_texCoord;
layout(location=2) in vec3 a_normal;

uniform mat4 u_sysMat;
uniform mat3 u_rotate;
uniform vec3 u_space;
uniform mat4 u_modelViewProject;

out vec3 v_point;
out vec2 v_texCoord;
out vec3 v_normal;

void main()
{
	v_point = (u_sysMat * vec4(a_point/u_space, 1.0)).xyz;
	gl_Position = u_modelViewProject * vec4(v_point, 1.0);
	v_texCoord = a_texCoord;
	v_normal = u_rotate * a_normal;
}

