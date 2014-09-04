//
//  PERealNode.cpp
//  Engine
//
//  Created by rocket99 on 14-9-4.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PERealNode.h"
#include "PELayer3D.h"

PERealNode::PERealNode():
m_sceneIn(NULL),
m_color(ColorRGBA(0.0f, 0.0f, 0.0f, 0.0f)),
m_texture(GL_FALSE),
m_program(GL_FALSE)
{}

PERealNode::~PERealNode(){}


void PERealNode::setSceneIn(PELayer3D *scene)
{
    m_sceneIn = scene;
    for(int i=0; i<m_children.size(); ++i){
        static_cast<PERealNode *>(m_children[i])->setSceneIn(scene);
    }
}

PELayer3D *PERealNode::getSceneIn()
{
    return m_sceneIn;
}

void PERealNode::addChild(PERealNode *node)
{
    PENode::addChild(node);
    node->setSceneIn(m_sceneIn);
}

void PERealNode::addChild(PERealNode *node, int tag)
{
    PENode::addChild(node, tag);
    node->setSceneIn(m_sceneIn);
}
void PERealNode::addChild(PERealNode *node, string name)
{
    PENode::addChild(node, name);
    node->setSceneIn(m_sceneIn);
}

void PERealNode::removeChild(PERealNode *node)
{
    node->setSceneIn(NULL);
    PENode::removeChild(node);
}
void PERealNode::removeChildByTag(int tag)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it)->getTag() == tag) {
            static_cast<PERealNode *>(*it)->setSceneIn(NULL);
            (*it)->release();
            m_children.erase(it);
        }else{
            ++ it;
        }
    }

}

void PERealNode::removeChildByName(string name)
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        if ((*it)->getName() == name) {
            static_cast<PERealNode *>(*it)->setSceneIn(NULL);
            (*it)->release();
            m_children.erase(it);
        }else{
            ++ it;
        }
    }
}

void PERealNode::removeAllChildern()
{
    std::vector<PENode *>::iterator it = m_children.begin();
    while(it != m_children.end()){
        static_cast<PERealNode *>(*it)->setSceneIn(NULL);
        (*it)->release();
        ++ it;
    }
}

void PERealNode::removeFromParentNode()
{
    PENode::removeFromParentNode();
    m_sceneIn = NULL;
}


void PERealNode::setLightUniformBlock(){
    m_sceneIn->getLightSource()->setUniformBlock(m_program);
}

void PERealNode::deleteLightUbo(){
    m_sceneIn->getLightSource()->removeUniformBlock();
}

void PERealNode::setModelViewProjectUniform()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_MODELPROJECT);
    if(loc >= 0){
        PEMatrix mat = m_sceneIn->getCamera()->modelViewProject();
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat.getData());
    }
}

PERealNode::Material & PERealNode::getMaterial(){
    return m_material;
}

void PERealNode::setMaterialUniformBlock(){
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

void PERealNode::deleteMaterialUbo()
{
    if(glIsBuffer(m_materialUbo) == GL_TRUE){
        glDeleteBuffers(1, &m_materialUbo);
    }
}

void PERealNode::setWorldMatUniform()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_SYSMAT);
    if(loc >= 0){
        this->setWorldMat();
        glUniformMatrix4fv(loc, 1, GL_FALSE, m_worldMat.getData());
    }
}

void PERealNode::setSpaceUniform()
{
    GLint loc = glGetUniformLocation(m_program, UNIFORM_SPACE);
    if(loc >=0){
        glUniform3f(loc, m_worldSize.x, m_worldSize.y, m_worldSize.z);
    }
}
void PERealNode::setColorUniform(){
    GLint loc = glGetUniformLocation(m_program, UNIFORM_COLOR);
    if(loc >= 0){
        glUniform4f(loc, m_color.r, m_color.g, m_color.b, m_color.a);
    }
}

void PERealNode::setGLProgram(GLuint prog){
    m_program = prog;
}

GLuint PERealNode::getGLProgram(){
    return m_program;
}

Color4F &PERealNode::Color(){
    return m_color;
}

GLuint &PERealNode::Texture(){
    return m_texture;
}
