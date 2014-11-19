#version 420

in vec3 v_point;
in vec2 v_texCoord;
in vec3 v_normal;

uniform u_light{
	vec4 l_ambient;
	vec4 l_diffuse;
	vec4 l_specular;
	vec3 l_position;
	vec3 l_direction;
	float l_fovy;
	float l_shininess;
};
//uniform u_light_struct u_light;

uniform u_material{
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	vec4 m_emission;
};
//uniform u_material_struct u_material;

uniform sampler2D u_texture;
uniform vec3 u_cameraPos;

layout(location=0) out vec4 frag_color;

float attenu(vec3 point){
	float s = length(l_position-point);
	return 1.0/(0.02*s*s + 0.3*s + 0.5);
}

vec4 light(vec3 point)
{
	vec4 ambient = vec4(0.0);
	vec4 diffuse = vec4(0.0);
	vec4 specular = vec4(0.0);

	ambient = m_ambient * l_ambient;
	vec3 n = normalize(v_normal);//顶点法线
	vec3 l0 = normalize(point-l_position);//入射光线
	vec3 l1 = reflect(n, l0);//出射光线
	diffuse = l_diffuse*m_diffuse*dot(n, l0);
	
	float angle = acos(dot(normalize(l_direction), l0));
	if(angle < l_fovy){
		vec3 s = normalize(normalize(u_cameraPos-point) - l0);
		float f = pow(max(dot(s, n), 0.0), l_shininess);
		specular = l_specular * m_specular * f;
	}
	return m_emission + ambient + (ambient + diffuse + specular)*attenu(point);
};

void main()
{
	frag_color = light(v_point)*texture(u_texture, v_texCoord);
}


