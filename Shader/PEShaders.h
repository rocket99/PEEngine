//
//  PEShaders.h
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef Engine_PEShaders_h
#define Engine_PEShaders_h

const char *commonVert  = "\
#version 300 ES     \
layout (location=0) in mediump vec3 a_point; \
layout (location=1) in mediump vec2 a_texCoord;\
uniform mediump vec3 u_position;\
uniform mediump vec3 u_space;\
uniform mediump mat4 u_rotate;\
void main()\
{\
    gl_PointSize=1.0;\
    vec4 tmp = vec4(a_point, 1.0)*u_rotate;\
    gl_Position = (tmp.xyz+u_position)/u_space;\
}";

const char *commonFrag = "\
#version 300 ES \
layout (location=1) int mediump vec2 v_texCoord;\
layout (location=0) out mediump vec4 frag_color;\
uniform sample2D u_texture;\
uniform mediump vec4 u_color;\
void main(){\
    frag_color = u_color;\
}";
#endif
