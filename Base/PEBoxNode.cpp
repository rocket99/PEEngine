//
//  PEBoxNode.cpp
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEBoxNode.h"

PEBoxNode::PEBoxNode(){}

PEBoxNode::~PEBoxNode(){

}

PEBoxNode *PEBoxNode::createWithSize(const Size3D &size)
{
    PEBoxNode *box = new PEBoxNode();
    if(box->initWithSize(size)){
        box->autoRelease();
        return box;
    }
    delete box;
    return NULL;
}

bool PEBoxNode::initWithSize(const Size3D &size)
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
    rect->Rotate(Point3D(0.0, 1.0, 0.0), 90.0);
    this->addChild(rect, "left");
    
    rect = PERect::create(m_size.z, m_size.y);
    rect->Position() = Point3D(0.5*m_size.x, 0.0, 0.0);
    rect->Rotate(Point3D(0.0, 1.0, 0.0), -90.0);
    this->addChild(rect, "right");
    
    rect = PERect::create(m_size.x, m_size.z);
    rect->Position() = Point3D(0.0, 0.5*m_size.y, 0.0);
    rect->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
    this->addChild(rect, "top");
    
    rect = PERect::create(m_size.x, m_size.z);
    rect->Position() = Point3D(0.0, -0.5*m_size.y, 0.0);
    rect->Rotate(Point3D(1.0, 0.0, 0.0), -90.0);
    this->addChild(rect, "bottom");
    
    return true;
}

PERect *PEBoxNode::getBoxSurfaceByName(string name)
{
    return static_cast<PERect *>(this->getChildByName(name));
}

void PEBoxNode::setGLProgram0(GLuint program)
{
    m_program0 = program;
    for (int i=0; i<m_children.size(); ++i) {
        static_cast<PERealNode *>(m_children[i])->Program0() = program;
    }
}

void PEBoxNode::setGLProgram1(GLuint program)
{
    m_program1 = program;
    for (int i=0; i<m_children.size(); ++i) {
        static_cast<PERealNode *>(m_children[i])->Program1() = program;
    }
}

void PEBoxNode::drawFBO(){
    PENode::drawFBO();
}

void PEBoxNode::draw(){
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
    PENode::draw();
//    glDisable(GL_BLEND);
}


