//
//  PELight.cpp
//  Engine
//
//  Created by rocket99 on 14-8-29.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELight.h"

PELight::PELight()
{
    
}

PELight::~PELight()
{
    
}

PELight *PELight::createWithWorld(const Size3D &size)
{
    PELight *light = new PELight;
    if(light->initWithWorld(size)){
        return light;
    }
    delete light;
    return NULL;
}

bool PELight::initWithWorld(const Size3D &size)
{
    m_world = size;
    m_worldPos = Point3D(0.0, m_world.y, 0.0);
    m_direct = Point3D(0.0, -1.0, 0.0);
    m_specularAngle = 180.0;
    
    return true;
}


