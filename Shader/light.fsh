#version 300 es
in mediump vec3 v_point;
in mediump vec2 v_texCoord;
in mediump vec3 v_normal;

layout (location = 0) out mediump vec4 frag_color;

uniform u_light
{
    mediump vec4 l_ambient;
    mediump vec4 l_diffuse;
    mediump vec4 l_specular;
    mediump vec3 l_position;
    mediump vec3 l_direction;
    mediump float l_fovy;
};

uniform u_material
{
    mediump vec4 m_ambient;
    mediump vec4 m_diffuse;
    mediump vec4 m_specular;
    mediump vec4 m_emission;
};

uniform mediump vec3 cameraPos;
uniform mediump float specularPower;

mediump vec4 light_color(mediump vec3 p)
{
    mediump vec4 ambient = l_ambient * m_ambient; //环境光
    
    mediump float    dis = length(p - l_position);
    mediump vec3 inLight = normalize(p - l_position);
    mediump vec3       n = normalize(v_normal);
    mediump vec3 outLine = reflect(n, inLight);
    mediump vec3     eye = normalize(cameraPos - v_point);
    //漫反射
    mediump vec4 diffuse = max(0.0, dot(eye, outLine))*l_diffuse*m_diffuse;
    //镜面反射
    mediump vec4 specular = pow(dis, 5.0)*max(0.0, dot(eye, outLine))*l_specular*m_specular;
}



void main()
{
    
}