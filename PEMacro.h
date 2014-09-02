//
//  PEMacro.h
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef Engine_PEMacro_h
#define Engine_PEMacro_h

#define GLOBAL_WORLD_SIZE       Point3D(768, 768, 768)

#define ATTRIB_POINT_LOC        0
#define ATTRIB_TEXCOORD_LOC     1
#define ATTRIB_NORMAL_LOC       2
#define ATTRIB_COLOR_LOC        3

#define UNIFORM_SPACE           "u_space"
#define UNIFORM_ROTATE          "u_rotate"
#define UNIFORM_SYSMAT          "u_sysMat"
#define UNIFORM_MODELPROJECT    "u_modelViewProject"
#define UNIFORM_COLOR           "u_color"
#define UNIFORM_TEXTURE         "u_texture"
#define UNIFORM_LIGHT           "u_light"
#define UNIFORM_MATERIAL        "u_material"

#define UNIFORM_LIGHT_BIND      1
#define UNIFORM_MATERIAL_BIND   0
#endif
