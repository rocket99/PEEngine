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
m_position(Point3D(0.0, 0.0, 0.0)),
m_isVisible(true),
m_color(ColorRGBA(0.0, 0.0, 0.0, 1.0))
{
    m_children.clear();
}

PENode::~PENode()
{
    
}

PENode *PENode::create()
{
    PENode *node = new PENode();
    if(node->init()){
        return node;
    }
    delete node;
    return NULL;
}

bool PENode::init()
{
    PEMatrix mat = PEMatrix::RotationMatrix(Point3D(0, 0, 1.0), 0.0);
    m_rotate = mat;
    return true;
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
        ++ it;
    }
    node->retain();
    node->setParentNode(this);
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
    node->setParentNode(this);
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
    node->setParentNode(this);
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
void PENode::removeAllChildern()
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->release();
        ++ it;
    }
}
void PENode::removeFromParentNode(){
    this->m_parent->removeChild(this);
}

PENode * PENode::getChildByTag(int tag)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it)->getTag() == tag) {
            return *it;
        }else{
            ++ it;
        }
    }
    return NULL;
}

PENode * PENode::getChildByName(string name)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it)->getName() == name) {
            return *it;
        }else{
            ++ it;
        }
    }
    return NULL;
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

void PENode::update()
{
    
}

void PENode::draw()
{
    this->update();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->update();
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

Color4F &PENode::Color()
{
    return m_color;
}

void PENode::setWorldPos()
{
    m_worldPos = this->m_position;
    PENode *parent = m_parent;
    while (parent != NULL) {
        m_worldPos += parent->Position();
        parent = parent->getParentNode();
    }
}

void PENode::setRotate(V3D axis, float angle)
{
    m_rotateAxis = axis;
    m_rotateAngle = angle;
    PEMatrix mat = PEMatrix::RotationMatrix(axis, angle);
    m_rotate = mat;
}

PEMatrix &PENode::getRotate()
{
    return m_rotate;
}

void PENode::setWorldRotate()
{
    m_worldRotate = m_rotate;
    PEMatrix mat = PEMatrix::IdentityMat(4);
    mat.Elm(0, 3) += m_position.x/m_worldSize.x;
    mat.Elm(1, 3) += m_position.y/m_worldSize.y;
    mat.Elm(2, 3) += m_position.z/m_worldSize.z;
    m_worldRotate = cross(mat, m_worldRotate);
    PENode *parent = m_parent;
    while (parent != NULL) {
        PEMatrix mat0 = parent->getRotate();
        PEMatrix mat1 = PEMatrix::IdentityMat(4);
        mat1.Elm(0, 3) = parent->Position().x / parent->World().x;
        mat1.Elm(1, 3) = parent->Position().y / parent->World().y;
        mat1.Elm(2, 3) = parent->Position().z / parent->World().z;
        PEMatrix mat2 = cross(mat1, mat0);
        m_worldRotate = cross(mat2, m_worldRotate);
        parent = parent->getParentNode();
    }
}

GLuint &PENode::Texture()
{
    return m_texture;
}