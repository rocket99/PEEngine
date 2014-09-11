#version 300 es
in mediump float v_depth;
layout (location=0) out mediump vec4 frag_color;

void main(){
    frag_color = vec4(v_depth-0.5, v_depth-0.5, v_depth-0.5, 1.0);
}

