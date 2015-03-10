#version 420

in vec2 v_texCoord;
uniform sampler2D u_texture;
//uniform sampler2D u_normalTex;

//uniform vec3 u_lightDirect;

layout(location=0) out vec4 frag_color;

void main(){
	vec3 lightDirect = vec3(-1.0, -1.5, -0.5);
//	vec4 texColor = texture(u_texture, v_texCoord);
	vec4 norColor = texture(u_texture, v_texCoord);
	vec3 normal = norColor.xyz*2.0-1.0;
	vec4 ambient = vec4(0.25, 0.25, 0.25, 0.25);
	float df = max(0.0, dot(normalize(lightDirect), normalize(normal)));
	vec4 diffuse = df*vec4(1.0, 1.0, 1.0, 1.0);
	frag_color = vec4(vec3(ambient+diffuse), diffuse.a);	
}
