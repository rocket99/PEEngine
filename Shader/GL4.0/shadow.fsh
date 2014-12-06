#version 420
in vec3 v_point;
in vec2 v_texCoord;
in vec3 v_normal;
in vec4 v_shadowCoord;

layout(location=0) out vec4 frag_color;

uniform u_light{
	vec4 l_ambient;
	vec4 l_diffuse;
	vec4 l_specular;
	vec3 l_position;
	vec3 l_direction;
	float l_fovy;
	float l_shininess;
};

uniform u_material{
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	vec4 m_emission;
};

uniform vec3 u_cameraPos;
uniform sampler2D u_texture;
uniform sampler2DShadow u_depthTex;

float attenu(vec3 P){
	float s = length(P-l_position);
	return 1.0/(0.01*s*s+0.3*s+1.5);
}

float shadow_factor()
{
	float sum = 0.0;
	float delta = 1.0/900.0;
	sum += textureProj(u_depthTex, v_shadowCoord+vec4(-delta, -delta, 0.0, 0.0));
	sum += textureProj(u_depthTex, v_shadowCoord+vec4(   0.0, -delta, 0.0, 0.0));
	sum += textureProj(u_depthTex, v_shadowCoord+vec4( delta, -delta, 0.0, 0.0));

	sum += textureProj(u_depthTex, v_shadowCoord+vec4(-delta, 0.0, 0.0, 0.0));
	sum += textureProj(u_depthTex, v_shadowCoord);
	sum += textureProj(u_depthTex, v_shadowCoord+vec4( delta, 0.0, 0.0, 0.0));

	sum += textureProj(u_depthTex, v_shadowCoord+vec4(-delta, delta, 0.0, 0.0));
	sum += textureProj(u_depthTex, v_shadowCoord+vec4(   0.0, delta, 0.0, 0.0));
	sum += textureProj(u_depthTex, v_shadowCoord+vec4( delta, delta, 0.0, 0.0));

	return sum/9.0;
}

vec4 lightShine(vec3 P){
	vec4 ambient = l_ambient * m_ambient;
	vec3 n = normalize(v_normal);
	vec3 l0 = normalize(P-l_position);//入射光线
	vec4 diffuse = l_diffuse * m_diffuse*max(0.0, dot(n, -l0));
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	float theta = acos(dot(normalize(l_direction), l0));
	if(theta < l_fovy){
		vec3 e0 = normalize(u_cameraPos-P);
		vec3 s = normalize(e0 - l0);
		float ff = pow(max(dot(n, s), 0.0), l_shininess);
		specular = ff * l_specular * m_specular;
	}
	if(l_fovy > 0.0){
		return ambient+diffuse+(ambient+diffuse+specular*shadow_factor())*attenu(P);
	}else{
		return ambient+diffuse*shadow_factor();
	}
	return vec4(0.0);
}

void main(){
	frag_color = lightShine(v_point) * texture(u_texture, v_texCoord);
}


