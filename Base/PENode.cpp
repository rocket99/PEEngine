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
m_parent(nullptr),
m_program(0),
m_position(Point3D(0.0, 0.0, 0.0)),
m_isVisible(true),
m_color(ColorRGBA(0.0, 0.0, 0.0, 1.0)),
m_locRotateAngle(0.0),
m_locRotateAxis(Point3D(0.0, 0.0, 0.0)),
m_worldSize(GLOBAL_WORLD_SIZE),
m_worldPos(P3DZERO),
m_sceneIn(NULL)
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

void PENode::setSceneIn(PELayer3D *scene)
{
    m_sceneIn = scene;
    for(int i=0; i<m_children.size(); ++i){
        m_children[i]->setSceneIn(scene);
    }
}

PELayer3D *PENode::getSceneIn()
{
    return m_sceneIn;
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
    node->setSceneIn(m_sceneIn);
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
    node->setSceneIn(m_sceneIn);
  
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
    node->setSceneIn(m_sceneIn);
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

std::vector<PENode *> &PENode::getChildren(){
    return m_children;
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

void PENode::setGLProgram(GLuint prog){
    m_program = prog;
}

GLuint PENode::getGLProgram(){
    return m_program;
}

void PENode::update(){

}

void PENode::draw(){
    if(!m_isVisible)
        return;
    
    this->update();
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
    
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
Color4F &PENode::Color(){
    return m_color;
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

GLuint &PENode::Texture(){
    return m_texture;
}

void PENode::setMaterialUniformBlock(){
    GLint index = glGetUniformBlockIndex(m_program, UNIFORM_MATERIAL);
    if(index == GL_INVALID_OPERATION || index == GL_INVALID_INDEX){
        return;
    }
    GLint blockSize;
    glGetActiveUniformBlockiv(m_program, index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    GLubyte *blockBuffer = (GLubyte *)malloc(sizeof(GLubyte)*blockSize);
    const char *name[] = {"m_ambient", "m_diffuse", "m_specular", "m_emission"};
    GLuint indices[4]; GLint offset[4];
    glGetUniformIndices(m_program, 4, name, indices);
    glGetActiveUniformsiv(m_program, 4, indices, GL_UNIFORM_OFFSET, offset);
    
    GLfloat ambient[] = {m_material.ambient.r, m_material.ambient.g, m_material.ambient.b, m_material.ambient.a};
    GLfloat diffuse[] = {m_material.diffuse.r, m_material.diffuse.g, m_material.diffuse.b, m_material.diffuse.a};
    GLfloat specular[] = {m_material.specular.r, m_material.specular.g, m_material.specular.b, m_material.specular.a};
    GLfloat emission[] = {m_material.emission.r, m_material.emission.g, m_material.emission.b, m_material.emission.a};
    memcpy(blockBuffer+offset[0], ambient, 4*sizeof(GLfloat));
    memcpy(blockBuffer+offset[1], diffuse, 4*sizeof(GLfloat));
    memcpy(blockBuffer+offset[2], specular, 4*sizeof(GLfloat));
    memcpy(blockBuffer+offset[3], emission, 4*sizeof(GLfloat));
    
    glUniformBlockBinding(m_program, index, 2);

    glGenBuffers(1, &m_materialUbo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_materialUbo);
    glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 2, m_materialUbo, 0, blockSize);
    free(blockBuffer);
}

void PENode::deleteMaterialUbo()
{
    if(glIsBuffer(m_materialUbo) == GL_TRUE){
        glDeleteBuffers(1, &m_materialUbo);
    }
}

void PENode::setModelViewProjectUniform()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_MODELPROJECT);
    if(loc >= 0){
        PEMatrix mat = m_sceneIn->getCamera()->modelViewProject();
//        PEMatrix mat = m_sceneIn->getCamera()->modelViewOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat.getData());
    }
}

void PENode::setWorldMatUniform()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_SYSMAT);
    if(loc >= 0){
        this->setWorldMat();
        glUniformMatrix4fv(loc, 1, GL_FALSE, m_worldMat.getData());
    }
}

void PENode::setSpaceUniform()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_SPACE);
    if(loc >=0){
        glUniform3f(loc, m_worldSize.x, m_worldSize.y, m_worldSize.z);
    }
}
void PENode::setColorUniform(){
    GLint loc = glGetUniformLocation(m_program, UNIFORM_COLOR);
    if(loc >= 0){
        glUniform4f(loc, m_color.r, m_color.g, m_color.b, m_color.a);
    }
}