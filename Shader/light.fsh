#version 300 es
in mediump vec3 v_point;
in mediump vec2 v_texCoord;
in mediump vec3 v_normal;
in mediump vec4 v_shadowCoord;

layout (location = 0) out mediump vec4 frag_color;

uniform u_light
{
    mediump vec4 l_ambient;
    mediump vec4 l_diffuse;
    mediump vec4 l_specular;
    mediump vec3 l_position;
    mediump vec3 l_direction;
    mediump float l_fovy;
    mediump float l_shininess;
};

uniform u_material
{
    mediump vec4 m_ambient;
    mediump vec4 m_diffuse;
    mediump vec4 m_specular;
    mediump vec4 m_emission;
};

uniform mediump vec3 u_cameraPos;
uniform mediump sampler2DShadow u_depthTex;
uniform sampler2D u_texture;

mediump float Pi = asin(1.0)*2.0;

mediump float attenu (mediump vec3 p){
    if(l_fovy == 0.0){
        return 1.0;
    }
    mediump float dis = length(p - l_position);
    return 1.0/(0.005*dis*dis + 0.5*dis + 1.0);
}

mediump float shadowFactor(){
    mediump float sum = 0.0;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(-0.003, -0.003, 0.0, 0.0)) * 0.05;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(0.0, -0.003, 0.0, 0.0)) *0.1;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(0.003, -0.003, 0.0, 0.0)) * 0.05;
    
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(-0.003, 0.0, 0.0, 0.0)) *0.1;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(0.0, 0.0, 0.0, 0.0)) *0.4;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(0.003, 0.0, 0.0, 0.0)) *0.1;
    
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(-0.003, 0.003, 0.0, 0.0)) *0.05;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(0.0, 0.003, 0.0, 0.0)) *0.1;
    sum += textureProj(u_depthTex, v_shadowCoord + vec4(0.003, 0.003, 0.0, 0.0)) *0.05;

    return sum;
}

mediump vec4 light_color(mediump vec3 p)
{
    mediump vec3 i = normalize(p - l_position);
    mediump vec3 n = normalize(v_normal);
    mediump vec3 o = normalize(reflect(i, n));
    
    mediump vec4 ambient = l_ambient * m_ambient; //环境光
    mediump vec4 diffuse = vec4(0.0);//散射光
    mediump vec4 specular = vec4(0.0);
    
    if (l_fovy == 0.0) {//平行光
        diffuse = max(0.0, dot(-normalize(l_direction), n))*l_diffuse*m_diffuse;
        mediump vec3 s = normalize((l_position-p)+(u_cameraPos-p));
        specular = l_specular*m_specular*pow(max(dot(s, n), 0.0), l_shininess);
    }else{
        ambient *= attenu(p);
        diffuse = l_diffuse*m_diffuse * max(0.0, dot(-i, n));
        mediump float angle = acos(dot(normalize(l_direction), i));
        if(dot(-i, n) > 0.0 && angle < l_fovy){
            mediump vec3 s = normalize((l_position-p)+(u_cameraPos-p));
            specular = l_specular*m_specular*pow(max(dot(s, n), 0.0), l_shininess);
        }
    }
    return (ambient + diffuse + specular);
}

void main(){
    frag_color = m_emission + light_color(v_point)*shadowFactor();// + 0.1*texture(u_texture, v_texCoord);
    frag_color *= texture(u_texture, v_texCoord);
}

