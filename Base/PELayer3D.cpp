//
//  PELayer.cpp
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELayer3D.h"
#include "PERealNode.h"

PELayer3D::PELayer3D():
m_size(Point3D(0, 0, 0)),
m_camera(NULL), m_light(NULL)
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
    m_size = size;
    m_camera = PECamera::create(size, Point3D(0.0, 0.0, size.z), P3DZERO, Point3D(0.0, 1.0, 0.0));
    m_camera->setPerspect(60.0, 1.0, 0.05, 30.0);
    m_camera->World() = m_size;
    m_camera->WorldFocus() = P3DZERO;
    m_camera->WorldPos() = Point3D(0.0, 0.0, m_size.z);
    m_camera->upDirect() = Point3D(0.0, 1.0, 0.0);
    
    m_light = PELight::createWithWorld(size);
    
    return true;
}

void PELayer3D::draw(){
    PENode::draw();
}

PECamera *PELayer3D::getCamera()
{
    return m_camera;
}

PELight *PELayer3D::getLightSource()
{
    return m_light;
}

void PELayer3D::addChild(PENode *node)
{
    PENode::addChild(node);
    static_cast<PERealNode *>(node)->setSceneIn(this);
}

void PELayer3D::addChild(PENode *node, int tag)
{
    PENode::addChild(node, tag);
    if(static_cast<PERealNode *>(node) != nullptr)
        static_cast<PERealNode *>(node)->setSceneIn(this);
}

void PELayer3D::addChild(PENode *node, string name)
{
    PENode::addChild(node, name);
    if(static_cast<PERealNode *>(node) != nullptr)
        static_cast<PERealNode *>(node)->setSceneIn(this);
}

void PELayer3D::removeChild(PENode *node)
{
    if(static_cast<PERealNode *>(node) != nullptr)
        static_cast<PERealNode *>(node)->setSceneIn(NULL);
    PENode::removeChild(node);
}

void PELayer3D::removeChildByTag(int tag)
{
    PENode *node = this->getChildByTag(tag);
    this->removeChild(node);
}

void PELayer3D::removeChildByName(string name)
{
    PENode *node = this->getChildByName(name);
    this->removeChild(node);
}

void PELayer3D::removeAllChildern(){
    PENode::removeAllChildern();
}


