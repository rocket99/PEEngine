//
//  PELight.cpp
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELight.h"

PELight::PELight()
{
    m_position = Point3D(0.0, 0.0, 0.0);
    m_direction = Point3D(0.0, -1.0, 0.0);
    m_world = Point3D(1.0, 1.0, 1.0);
    m_ambient = ColorRGBA(0.1, 0.1, 0.1, 0.1);
    m_diffuse = ColorRGBA(0.5, 0.5, 0.5, 0.5);
    m_specular = ColorRGBA(1.0, 1.0, 1.0, 1.0);
    m_fovy = 180.0;
    m_camera = NULL;
}

PELight::~PELight()
{
    if(m_camera != NULL){
        delete m_camera;
    }
}

PELight * PELight::createWithWorld(const Size3D &world)
{
    PELight *light = new PELight;
    if(light->initWithWorld(world)) {
        return light;
    }
    delete light;
    return NULL;
}

bool PELight::initWithWorld(const Size3D &world)
{
    if(world.x*world.y*world.z == 0.0 ){
        return false;
    }
    m_world = world;
    return true;
}

