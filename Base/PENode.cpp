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
m_parent(NULL),
m_position(Point3D(0.0, 0.0, 0.0)),
//m_locRotateAngle(0.0),
//m_locRotateAxis(Point3D(0.0, 0.0, 0.0)),
m_worldSize(GLOBAL_WORLD_SIZE),
m_worldPos(P3DZERO),
m_scale(Point3D(1.0, 1.0, 1.0)),
m_locEuler(P3DZERO)
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
    this->setRotate(P3DZERO, PENode::Euler_XYZ);
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
    if(NULL == node){
        return;
    }
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
    if(NULL == node){
        return;
    }
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
    if(NULL == node){
        return;
    }
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
    if(node != NULL){
        this->removeChild(node);
    }
}

void PENode::removeChildByName(string name)
{
    PENode *node = this->getChildByName(name);
    if(node != NULL){
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
    if(!m_isVisible){
        return;
    }
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->draw();
        ++ it;
    }
}

void PENode::drawFBO()
{
    if(!m_isVisible){
        return;
    }
    this->update();
    
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        (*it)->drawFBO();
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

P3D &PENode::Scale()
{
    return m_scale;
}

float &PENode::ScaleX()
{
    return m_scale.x;
}

float &PENode::ScaleY()
{
    return m_scale.y;
}

float &PENode::ScaleZ()
{
    return m_scale.z;
}

void PENode::Rotate(V3D axis, float angle){

    m_localRotate = cross(PEMatrix::RotationMatrix(axis, angle), m_localRotate);
	m_localRotate.display();
}

void PENode::setRotate(P3D EulerAngle, EulerOrder order)
{
    m_locEuler = EulerAngle;
    PEMatrix matAlpha = PEMatrix::RotationMatrix(Point3D(0.0, 0.0, 1.0), EulerAngle.x);
    PEMatrix matBeta = PEMatrix::RotationMatrix(Point3D(0.0, 1.0, 0.0), EulerAngle.y);
    PEMatrix matGama = PEMatrix::RotationMatrix(Point3D(0.0, 0.0, 1.0), EulerAngle.z);
    m_localRotate = cross(matAlpha, cross(matBeta, matGama));
}


PEMatrix &PENode::RotateMatrix(){
    return m_localRotate;
}


P3D &PENode::EulerRotate()
{
    return m_locEuler;
}

void PENode::setWorldMat(){
    PEMatrix mat = PEMatrix::IdentityMat(4);
    mat.Elm(0, 3) += m_position.x/m_worldSize.x;
    mat.Elm(1, 3) += m_position.y/m_worldSize.y;
    mat.Elm(2, 3) += m_position.z/m_worldSize.z;
    mat.Elm(0, 0) *= m_scale.x;
    mat.Elm(1, 1) *= m_scale.y;
    mat.Elm(2, 2) *= m_scale.z;
    m_worldMat = cross(mat, m_localRotate);
    PENode *parent = m_parent;
    while (parent != NULL) {
        PEMatrix mat1 = PEMatrix::IdentityMat(4);
        mat1.Elm(0, 3) = parent->Position().x / parent->World().x;
        mat1.Elm(1, 3) = parent->Position().y / parent->World().y;
        mat1.Elm(2, 3) = parent->Position().z / parent->World().z;
        mat1.Elm(0, 0) *= parent->ScaleX();
        mat1.Elm(1, 1) *= parent->ScaleY();
        mat1.Elm(2, 2) *= parent->ScaleZ();
        m_worldMat = cross(cross(mat1, parent->RotateMatrix()), m_worldMat);
        parent = parent->getParentNode();
    }
}










