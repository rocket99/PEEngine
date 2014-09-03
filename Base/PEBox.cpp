//
//  PEBox.cpp
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEBox.h"

PEBox::PEBox(){}

PEBox::~PEBox(){

}

PEBox *PEBox::createWithSize(const Size3D &size)
{
    PEBox *box = new PEBox();
    if(box->initWithSize(size)){
        return box;
    }
    delete box;
    return NULL;
}

bool PEBox::initWithSize(const Size3D &size)
{
    if(!PENode::init()){
        return false;
    }
    m_size = size;
    
    PERect *rect = NULL;
    rect = PERect::create(m_size.x, m_size.y);
    rect->Position() = Point3D(0.0, 0.0, 0.5*m_size.z);
    this->addChild(rect, "front");
    
    rect = PERect::create(m_size.x, m_size.y);
    rect->Position() = Point3D(0.0, 0.0, -0.5*m_size.z);
    this->addChild(rect, "back");
    
    rect = PERect::create(m_size.z, m_size.y);
    rect->Position() = Point3D(-0.5*m_size.x, 0.0, 0.0);
    rect->setRotate(Point3D(0.0, 1.0, 0.0), 90.0);
    this->addChild(rect, "left");
    
    rect = PERect::create(m_size.z, m_size.y);
    rect->Position() = Point3D(0.5*m_size.x, 0.0, 0.0);
    rect->setRotate(Point3D(0.0, 1.0, 0.0), -90.0);
    this->addChild(rect, "right");
    
    rect = PERect::create(m_size.x, m_size.z);
    rect->Position() = Point3D(0.0, 0.5*m_size.y, 0.0);
    rect->setRotate(Point3D(1.0, 0.0, 0.0), 90.0);
    this->addChild(rect, "top");
    
    rect = PERect::create(m_size.x, m_size.z);
    rect->Position() = Point3D(0.0, -0.5*m_size.y, 0.0);
    rect->setRotate(Point3D(1.0, 0.0, 0.0), -90.0);
    this->addChild(rect, "bottom");
    
    return true;
}

PERect *PEBox::getBoxSurfaceByName(string name)
{
    return static_cast<PERect *>(this->getChildByName(name));
}

void PEBox::setGLProgram(GLuint program)
{
    m_program = program;
    for (int i=0; i<m_children.size(); ++i) {
        m_children[i]->setGLProgram(program);
    }
}



