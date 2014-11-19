#version 420

layout(location=0) in vec3 a_point;
layout(location=1) in vec2 a_texCoord;
layout(location=2) in vec3 a_normal;

uniform vec3 u_space;
uniform mat3 u_rotate;
uniform mat4 u_sysMat;
uniform mat4 u_modelViewProject;
uniform mat4 u_lightViewProject;

out vec3 v_point;
out vec3 v_normal;
out vec2 v_texCoord;
out vec4 v_shadowCoord;
void main()
{
	mat4 B;
	B[0] = vec4(0.5, 0.0, 0.0, 0.0);
	B[1] = vec4(0.0, 0.5, 0.0, 0.0);
	B[2] = vec4(0.0, 0.0, 0.5, 0.0);
	B[3] = vec4(0.5, 0.5, 0.5, 1.0);

	v_point = (u_sysMat * vec4(a_point/u_space, 1.0)).xyz;
	v_normal = u_rotate * a_normal;
	v_texCoord = a_texCoord;
	v_shadowCoord = B * u_lightViewProject*vec4(v_point, 1.0);
	gl_Position = u_modelViewProject*vec4(v_point, 1.0);
}


