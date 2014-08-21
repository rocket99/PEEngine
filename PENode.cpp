//
//  PENode.cpp
//  Engine
//
//  Created by rocket99 on 14-8-20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PENode.h"

PENode::PENode():
m_tag(0),
m_parent(nullptr),
m_program(0),
m_posiiton(Point3D(0, 0, 0))
{
    m_children.clear();
}

PENode::~PENode()
{
    
}


void PENode::setTag(int value)
{
    m_tag = value;
}

int PENode::getTag()
{
    return m_tag;
}


void PENode::addChild(PENode *node)
{
    node->retain();
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if (*it == node) {
            return;
        }
    }
    this->m_children.push_back(node);
}

void PENode::addChild(PENode *node, int tag)
{
    node->setTag(tag);
    node->retain();
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if (*it == node) {
            return;
        }
    }
    this->m_children.push_back(node);
}

void PENode::removeFromParentNode()
{
    
    this->release();
    
}

void PENode::setParentNode(PENode *node)
{
    this->m_parent = node;
}

PENode * PENode::getParentNode()
{
    return m_parent;
}

void PENode::setGLProgram(GLuint prog)
{
    m_program = prog;
}

GLuint PENode::getGLProgram()
{
    return m_program;
}

void PENode::draw()
{
    
}