#version 420

layout(location=0) in vec3 a_point;
out vec2 v_point;

void main(){
	gl_Position = vec4(a_point, 1.0);
	v_point = a_point.xy;
}
