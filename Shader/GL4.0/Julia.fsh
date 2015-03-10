#version 420

in vec2 v_point;

layout(location=0) out vec4 frag_color;

vec2 multiple(vec2 A, vec2 B)
{
	return vec2(A.x*B.x-A.y*B.y, 2.0*A.x*B.y);
}

float Julia(vec2 p){
	vec2 z = p;
	float i=0.0;
	while(i<5.0 && length(z)<3.0){
		z= multiple(z, z) + vec2(-1.0, 1.0);
		i += 0.25;
	}
	return i/5.0;
}

float Mandelbrot(vec2 p)
{
	vec2 z= vec2(0.0);
	float i = 0.0;
	while(i<5.0 && length(z)<3.0){
		z = multiple(z, z) + p;
		i += 0.025;
	}
	return i/5.0;
}

void main(){
	float i = Julia(v_point * 3.0);
	frag_color = vec4(sin(i*3.1416), cos(i*3.1416), sin((i+0.15)*3.1416), 1.0);
}
