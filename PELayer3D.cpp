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
    return true;
}

void PELayer3D::draw(){
    PENode::draw();
}

