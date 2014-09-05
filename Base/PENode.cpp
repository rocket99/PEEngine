//
//  PENode.cpp
//  Engine
//
//  Created by rocket99 on 14-8-20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PENode.h"
#include "PELayer3D.h"

PENode::PENode():
m_tag(0),
m_isVisible(true),
m_parent(nullptr),
m_position(Point3D(0.0, 0.0, 0.0)),
m_locRotateAngle(0.0),
m_locRotateAxis(Point3D(0.0, 0.0, 0.0)),
m_worldSize(GLOBAL_WORLD_SIZE),
m_worldPos(P3DZERO)
{
    m_children.clear();
}

PENode::~PENode()
{
    this->removeAllChildern();
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
    this->setRotate(Point3D(0.0, 0.0, 1.0), 0.0);
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
    
    for (int i=0; i<node->getChildren().size(); ++i) {
        node->getChildren()[i]->retain();
    }
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
    
    for (int i=0; i<node->getChildren().size(); ++i) {
        node->getChildren()[i]->retain();
    }
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
    
    for (int i=0; i<node->getChildren().size(); ++i) {
        node->getChildren()[i]->retain();
    }
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
    node->setParentNode(NULL);
    for (int i=0; i<node->getChildren().size(); ++i) {
        node->getChildren()[i]->release();
    }
}

void PENode::removeChildByTag(int tag)
{
    PENode *node = this->getChildByTag(tag);
    if(node != nullptr){
        this->removeChild(node);
    }
}

void PENode::removeChildByName(string name)
{
    PENode *node = this->getChildByName(name);
    if(node != nullptr){
        this->removeChild(node);
    }
}

void PENode::removeAllChildern()
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->release();
        ++ it;
    }
    m_children.clear();
}

std::vector<PENode *> &PENode::getChildren(){
    return m_children;
}

void PENode::removeFromParentNode(){
    this->m_parent->removeChild(this);
    for (int i=0; i<m_children.size(); ++i) {
        m_children[i]->release();
    }
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

void PENode::update(){

}

void PENode::draw(){
    if(!m_isVisible)
        return;
    
    this->update();
    
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->update();
        (*it)->draw();
        ++ it;
    }
}

P3D &PENode::Position(){
    return m_position;
}
P3D &PENode::World(){
    return m_worldSize;
}
bool &PENode::Visible(){
    return m_isVisible;
}

void PENode::setRotate(V3D axis, float angle){
    m_locRotateAxis = axis;
    m_locRotateAngle = angle;
    m_localRotate  = PEMatrix::RotationMatrix(m_locRotateAxis, m_locRotateAngle);
}

PEMatrix &PENode::getRotate(){
    return m_localRotate;
}

V3D &PENode::RotateAxis(){
    return  m_locRotateAxis;
}

float &PENode::RotateAngle(){
    return m_locRotateAngle;
}

void PENode::setWorldMat(){
    PEMatrix mat = PEMatrix::IdentityMat(4);
    mat.Elm(0, 3) += m_position.x/m_worldSize.x;
    mat.Elm(1, 3) += m_position.y/m_worldSize.y;
    mat.Elm(2, 3) += m_position.z/m_worldSize.z;
    m_worldMat = cross(mat, m_localRotate);
    PENode *parent = m_parent;
    while (parent != NULL) {
        PEMatrix mat1 = PEMatrix::IdentityMat(4);
        mat1.Elm(0, 3) = parent->Position().x / parent->World().x;
        mat1.Elm(1, 3) = parent->Position().y / parent->World().y;
        mat1.Elm(2, 3) = parent->Position().z / parent->World().z;
        m_worldMat = cross(cross(mat1, parent->getRotate()), m_worldMat);
        parent = parent->getParentNode();
    }
}











