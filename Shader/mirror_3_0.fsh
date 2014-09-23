#version 300 es

in mediump vec3 v_point;
in mediump vec2 v_texCoord;
in mediump vec3 v_normal;

layout (location=0) out mediump vec4 frag_color;

uniform samplerCube u_skyBox;
uniform mediump vec3 u_cameraPos;

void main()
{
    mediump vec3 l0 = normalize(v_point - u_cameraPos);
    mediump vec3 l1 = normalize(v_normal);
    mediump vec3 l2 = normalize(reflect(l1, l0));
    
    frag_color = texture(u_skyBox, l2);
}

