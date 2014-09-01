//
//  PELight.h
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PELight__
#define __Engine__PELight__

#include <iostream>
#include "PEMath.h"

class PELight
{
public:
    PELight();
    ~PELight();
    static PELight *createWithWorld(const Size3D &world);
    bool initWithWorld(const Size3D &world);
    
    Size3D &World();
    P3D &Position();
    V3D &Direction();
    
    Color4F & Ambient();
    Color4F & Diffuse();
    Color4F & Specular();
    float & Fovy();
private:
    Size3D m_world;
    P3D m_position;
    V3D m_direction;
    Color4F m_ambient, m_diffuse, m_specular;
    float m_fovy;
    
    PECamera *m_camera;
    GLuint m_ubo;
};
#endif /* defined(__Engine__PELight__) */
