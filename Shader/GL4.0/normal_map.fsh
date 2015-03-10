#version 420

in vec4 v_color;
in vec2 v_texCoord;

layout(location=0) out vec4 frag_color;
uniform sampler2D u_normalTex;
uniform sampler2D u_colorTex;
uniform vec3 u_lightPos;
uniform vec3 u_lightDirect;
uniform vec4 u_ambient;
uniform vec4 u_diffuse;

void main(){
	vec4 texColor = texture(u_colorTex, v_texCoord);
	vec4 normal = texture(u_normalTex, v_texCoord);
	frag_color = texColor*normal;
}


