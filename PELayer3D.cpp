//
//  PELayer.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELayer3D.h"

PELayer3D::PELayer3D():m_size(Point3D(0, 0, 0))
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
    if(!PENode::init()){
        return false;
    }
    m_size = size;
    PECamera::getInstance()->setPerspect(60.0, 1.0, 0.05, 30.0);
    PECamera::getInstance()->World() = m_size;
    PECamera::getInstance()->WorldFocus() = P3DZERO;
    PECamera::getInstance()->WorldPos() = Point3D(0.0, 0.0, m_size.z);
    return true;
}

void PELayer3D::draw(){
//    PEMatrix modelProject = PECamera::getInstance()->modelViewProject();
    PENode::draw();
}

