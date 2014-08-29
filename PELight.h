//
//  PELight.h
//  Engine
//
//  Created by rocket99 on 14-8-29.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PELight__
#define __Engine__PELight__

#include <iostream>
#include "PEPrefix.h"
#include "PEMath.h"
#include "PEObject.h"

class PELight:public PEObject
{
public:
    PELight();
    ~PELight();
    static PELight *createWithWorld(const Size3D &size);
    bool initWithWorld(const Size3D &size);
private:
    P3D m_world, m_worldPos;
    P3D m_pos;
    V3D m_direct;
    float m_specularAngle;
    Color4F m_ambient, m_diffuse, m_specular;
    PECamera *m_camera;
};
#endif /* defined(__Engine__PELight__) */
