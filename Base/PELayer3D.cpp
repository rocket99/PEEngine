//
//  PELayer.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELayer3D.h"

PELayer3D::PELayer3D():m_size(Point3D(0, 0, 0)), m_camera(NULL)
{}

PELayer3D::~PELayer3D()
{}

PELayer3D *PELayer3D::create(const Size3D &size)
{
    PELayer3D *layer = new PELayer3D;
    if(layer->initWithSize(size)){
        return layer;
    }
    delete layer;
    return NULL;
}

bool PELayer3D::initWithSize(const Size3D &size)
{
    if(!PENode::init() || size.x * size.y * size.z == 0.0){
        return false;
    }
    m_sceneIn = this;
    m_size = size;
    m_camera = PECamera::create(size, Point3D(0.0, 0.0, size.z), P3DZERO, Point3D(0.0, 1.0, 0.0));
    m_camera->setPerspect(60.0, 1.0, 0.05, 30.0);
    m_camera->World() = m_size;
    m_camera->WorldFocus() = P3DZERO;
    m_camera->WorldPos() = Point3D(0.0, 0.0, m_size.z);
    m_camera->upDirect() = Point3D(0.0, 1.0, 0.0);
    return true;
}

void PELayer3D::draw(){
    PENode::draw();
}

PECamera *PELayer3D::getCamera()
{
    return m_camera;
}
