#version 300 es

layout (location = 0) in mediump vec3 a_point;
layout (location = 1) in mediump vec2 a_texCoord;
layout (location = 2) in mediump vec3 a_normal;

out mediump vec3 v_point;
out mediump vec2 v_texCoord;
out mediump vec3 v_normal;

uniform mediump vec3 u_space;
uniform mediump mat4 u_sysMat;
uniform mediump mat4 u_modelViewProject;
uniform mediump mat3 u_rotate;

void main()
{
    gl_PointSize = 1.0;
    gl_Position = u_modelViewProject * u_sysMat * vec4(a_point/u_space, 1.0);
    v_point = (u_sysMat * vec4(a_point, 1.0)).xyz / u_space;
    v_normal = u_rotate * a_normal;
    v_texCoord = a_texCoord;
}
