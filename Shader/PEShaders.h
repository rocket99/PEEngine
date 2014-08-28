//
//  PEShaders.h
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef Engine_PEShaders_h
#define Engine_PEShaders_h

#ifdef __cplusplus
extern "C" {
#endif
static const char *commonVertSrc  =
    "#version 300 es\n"
    "layout (location=0) in mediump vec3 a_point;\n"
    "layout (location=1) in mediump vec2 a_texCoord;\n"
    "uniform mediump vec3 u_position;\n"
    "uniform mediump vec3 u_space;\n"
    "uniform mediump mat4 u_rotate;\n"
    "out mediump vec2 v_texCoord;\n"
    "void main()\n"
    "{\n"
    "gl_PointSize=1.0;\n"
//    "vec4 tmp = vec4(a_point, 1.0)*u_rotate;\n"
    "gl_Position = u_rotate * vec4(a_point/u_space, 1.0);\n"
//    "gl_Position.w = 1.0;"
    "v_texCoord = a_texCoord;\n"
    "}\n";

static const char *commonFragSrc =
    "#version 300 es\n"
    "in mediump vec2 v_texCoord;\n"
    "layout (location=0) out mediump vec4 frag_color;\n"
    "uniform sampler2D u_texture;\n"
    "uniform mediump vec4 u_color;\n"
    "void main(){\n"
        "frag_color = mix(u_color, texture(u_texture, v_texCoord), 0.5);\n"
    "}\n";
#ifdef __cplusplus
}
#endif
#endif
