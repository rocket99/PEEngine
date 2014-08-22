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
m_position(Point3D(0, 0, 0)),
m_isVisible(true)
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
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if (*it == node) {
            return;
        }
    }
    node->retain();
    this->m_children.push_back(node);
}

void PENode::addChild(PENode *node, int tag)
{
    node->setTag(tag);
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if (*it == node) {
            return;
        }
        ++ it;
    }
    node->retain();
    this->m_children.push_back(node);
}

void PENode::addChild(PENode *node, string name)
{
    node->setName(name.c_str());
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if (*it == node) {
            return;
        }
        ++ it;
    }
    node->retain();
    this->m_children.push_back(node);
}

void PENode::removeChild(PENode *node)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it) == node) {
            m_children.erase(it);
            node->release();
        }else{
            ++ it;
        }
    }
}
void PENode::removeChildByTag(int tag)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it)->getTag() == tag) {
            (*it)->release();
            m_children.erase(it);
        }else{
            ++ it;
        }
    }
}

void PENode::removeChildByName(string name)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it)->getName() == name) {
            (*it)->release();
            m_children.erase(it);
        }else{
            ++ it;
        }
    }
}

void PENode::removeFromParentNode(){
    this->m_parent->removeChild(this);
}

void PENode::setParentNode(PENode *node){
    this->m_parent = node;
}

PENode * PENode::getParentNode(){
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
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->draw();
        ++ it;
    }
}

P3D &PENode::Position()
{
    return m_position;
}

P3D &PENode::World()
{
    return m_worldSize;
}
bool &PENode::Visible()
{
    return m_isVisible;
}

P3D PENode::getWorldPos()
{
    P3D result = this->m_position;
    PENode *parent = m_parent;
    while (parent != NULL) {
        result += parent->Position();
        parent = parent->getParentNode();
    }
    return result;
}
