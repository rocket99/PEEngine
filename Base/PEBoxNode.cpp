//
//  PEBoxNode.cpp
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEBoxNode.h"

PEBoxNode::PEBoxNode(){}

PEBoxNode::~PEBoxNode(){}

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

bool PEBoxNode::initWithSize(const Size3D &size){
    if(!PENode::init()){
        return false;
    }
    m_size = size;
    m_coords = new P3D[24];
    m_normal = new P3D[24];
    m_color = new Color4F[24];
    m_texCoord = new P2D[24];
    
    this->initFrontRect();
    this->initBackRect();
    this->initLeftRect();
    this->initRightRect();
    this->initTopRect();
    this->initBottomRect();
    m_data = new GLfloat[36*12];
    this->updateData();
    return true;
}

PERect *PEBoxNode::getBoxSurfaceByName(string name)
{
    return static_cast<PERect *>(this->getChildByName(name));
}

void PEBoxNode::setGLProgram0(GLuint program)
{
    m_program0 = program;
}

void PEBoxNode::setGLProgram1(GLuint program)
{
    m_program1 = program;
}

void PEBoxNode::drawFBO(){
    this->update();
    if(!m_isVisible){
        return;
    }
    PENode::drawFBO();
    m_program = m_program0;
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    this->updateData();
    glUseProgram(m_program);
    this->setLightProjectViewUniform(UNIFORM_MODELPROJECT);
    this->drawFunc();
}

void PEBoxNode::draw(){
   
    if(!m_isVisible){
        return;
    }
    PENode::draw();
    m_program = m_program1;
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    glUseProgram(m_program);
    this->setModelViewProjectUniform();
    this->setLightProjectViewUniform();
    this->setDepthTexUnifrom();
    this->setTextureUniform();
    this->drawFunc();
}

void PEBoxNode::drawFunc()
{
    this->setSpaceUniform();
    this->setWorldMatUniform();
    this->setColorUniform();
    this->setTextureUniform();
    this->setCameraPosUniform();
    GLint loc = glGetUniformLocation(m_program, UNIFORM_ROTATE);
    if(loc >= 0){
        PEMatrix mat = m_worldMat.complement(3, 3);
        glUniformMatrix3fv(loc, 1, GL_FALSE, mat.getData());
    }
    this->setMaterialUniformBlock();
    this->setLightUniformBlock();
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, &m_data[0]);
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glVertexAttribPointer(ATTRIB_NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, &m_data[36*3]);
    glEnableVertexAttribArray(ATTRIB_NORMAL_LOC);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, &m_data[36*6]);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glVertexAttribPointer(ATTRIB_COLOR_LOC, 4, GL_FLOAT, GL_FALSE, 0, &m_data[36*8]);
    glEnableVertexAttribArray(ATTRIB_COLOR_LOC);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glDisableVertexAttribArray(ATTRIB_POINT_LOC);
    glDisableVertexAttribArray(ATTRIB_NORMAL_LOC);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glDisableVertexAttribArray(ATTRIB_COLOR_LOC);
    
    this->deleteMaterialUbo();
    this->deleteLightUbo();
}

void PEBoxNode::initFrontRect()
{
    m_coords[0] = Point3D(-0.5*m_size.x, -0.5*m_size.y, 0.5*m_size.z);
    m_coords[1] = Point3D(-0.5*m_size.x,  0.5*m_size.y, 0.5*m_size.z);
    m_coords[2] = Point3D( 0.5*m_size.x,  0.5*m_size.y, 0.5*m_size.z);
    m_coords[3] = Point3D( 0.5*m_size.x, -0.5*m_size.y, 0.5*m_size.z);
    
    m_normal[0] = Point3D(0.0, 0.0, 1.0);
    m_normal[1] = m_normal[0];
    m_normal[2] = m_normal[1];
    m_normal[3] = m_normal[2];
    
    m_texCoord[0] = Point2D(0.0, 0.0);
    m_texCoord[1] = Point2D(0.0, 1.0);
    m_texCoord[2] = Point2D(1.0, 1.0);
    m_texCoord[3] = Point2D(1.0, 0.0);
}

void PEBoxNode::initBackRect()
{
    m_coords[4] = Point3D(-0.5*m_size.x, -0.5*m_size.y, -0.5*m_size.z);
    m_coords[5] = Point3D(-0.5*m_size.x,  0.5*m_size.y, -0.5*m_size.z);
    m_coords[6] = Point3D( 0.5*m_size.x,  0.5*m_size.y, -0.5*m_size.z);
    m_coords[7] = Point3D( 0.5*m_size.x, -0.5*m_size.y, -0.5*m_size.z);
    
    m_normal[4] = Point3D(0.0, 0.0, -1.0);
    m_normal[5] = m_normal[4];
    m_normal[6] = m_normal[5];
    m_normal[7] = m_normal[6];
    
    m_texCoord[4] = Point2D(0.0, 0.0);
    m_texCoord[5] = Point2D(0.0, 1.0);
    m_texCoord[6] = Point2D(1.0, 1.0);
    m_texCoord[7] = Point2D(1.0, 0.0);
}

void PEBoxNode::initLeftRect()
{
    m_coords[8] = Point3D(-0.5*m_size.x, -0.5*m_size.y, -0.5*m_size.z);
    m_coords[9] = Point3D(-0.5*m_size.x, -0.5*m_size.y,  0.5*m_size.z);
    m_coords[10] = Point3D(-0.5*m_size.x,  0.5*m_size.y,  0.5*m_size.z);
    m_coords[11] = Point3D(-0.5*m_size.x,  0.5*m_size.y, -0.5*m_size.z);
  
    m_normal[9] = Point3D(-1.0, 0.0, 0.0);
    m_normal[10] = m_normal[9];
    m_normal[11] = m_normal[10];
    m_normal[12] = m_normal[11];
    
    m_texCoord[8] = Point2D(0.0, 0.0);
    m_texCoord[9] = Point2D(0.0, 1.0);
    m_texCoord[10] = Point2D(1.0, 1.0);
    m_texCoord[11] = Point2D(1.0, 0.0);
}

void PEBoxNode::initRightRect()
{
    m_coords[12] = Point3D(0.5*m_size.x, -0.5*m_size.y, -0.5*m_size.z);
    m_coords[13] = Point3D(0.5*m_size.x, -0.5*m_size.y,  0.5*m_size.z);
    m_coords[14] = Point3D(0.5*m_size.x,  0.5*m_size.y,  0.5*m_size.z);
    m_coords[15] = Point3D(0.5*m_size.x,  0.5*m_size.y, -0.5*m_size.z);
    
    m_normal[12] = Point3D(1.0, 0.0, 0.0);
    m_normal[13] = m_normal[12];
    m_normal[14] = m_normal[13];
    m_normal[15] = m_normal[14];
    
    m_texCoord[12] = Point2D(0.0, 0.0);
    m_texCoord[13] = Point2D(0.0, 1.0);
    m_texCoord[14] = Point2D(1.0, 1.0);
    m_texCoord[15] = Point2D(1.0, 0.0);
}

void PEBoxNode::initTopRect()
{
    m_coords[16] = Point3D(-0.5*m_size.x, 0.5*m_size.y, -0.5*m_size.z);
    m_coords[17] = Point3D(-0.5*m_size.x, 0.5*m_size.y,  0.5*m_size.z);
    m_coords[18] = Point3D( 0.5*m_size.x, 0.5*m_size.y,  0.5*m_size.z);
    m_coords[19] = Point3D( 0.5*m_size.x, 0.5*m_size.y, -0.5*m_size.z);
    
    m_normal[16] = Point3D(0.0, 1.0, 0.0);
    m_normal[17] = m_normal[16];
    m_normal[18] = m_normal[17];
    m_normal[19] = m_normal[18];
    
    m_texCoord[16] = Point2D(0.0, 0.0);
    m_texCoord[17] = Point2D(0.0, 1.0);
    m_texCoord[18] = Point2D(1.0, 1.0);
    m_texCoord[19] = Point2D(1.0, 0.0);
}

void PEBoxNode::initBottomRect()
{
    m_coords[20] = Point3D(-0.5*m_size.x, -0.5*m_size.y, -0.5*m_size.z);
    m_coords[21] = Point3D(-0.5*m_size.x, -0.5*m_size.y,  0.5*m_size.z);
    m_coords[22] = Point3D( 0.5*m_size.x, -0.5*m_size.y,  0.5*m_size.z);
    m_coords[23] = Point3D( 0.5*m_size.x, -0.5*m_size.y, -0.5*m_size.z);
    
    m_normal[20] = Point3D(0.0, -1.0, 0.0);
    m_normal[21] = m_normal[20];
    m_normal[22] = m_normal[21];
    m_normal[23] = m_normal[22];
    
    m_texCoord[20] = Point2D(0.0, 0.0);
    m_texCoord[21] = Point2D(0.0, 1.0);
    m_texCoord[22] = Point2D(1.0, 1.0);
    m_texCoord[23] = Point2D(1.0, 0.0);
}

void PEBoxNode::updateData()
{
    int k=0;
    for (int i=0; i<6; ++i) {
        m_data[k++] = m_coords[4*i+0].x;
        m_data[k++] = m_coords[4*i+0].y;
        m_data[k++] = m_coords[4*i+0].z;
        
        m_data[k++] = m_coords[4*i+1].x;
        m_data[k++] = m_coords[4*i+1].y;
        m_data[k++] = m_coords[4*i+1].z;
        
        m_data[k++] = m_coords[4*i+2].x;
        m_data[k++] = m_coords[4*i+2].y;
        m_data[k++] = m_coords[4*i+2].z;
        
        m_data[k++] = m_coords[4*i+0].x;
        m_data[k++] = m_coords[4*i+0].y;
        m_data[k++] = m_coords[4*i+0].z;
        
        m_data[k++] = m_coords[4*i+2].x;
        m_data[k++] = m_coords[4*i+2].y;
        m_data[k++] = m_coords[4*i+2].z;
        
        m_data[k++] = m_coords[4*i+3].x;
        m_data[k++] = m_coords[4*i+3].y;
        m_data[k++] = m_coords[4*i+3].z;
    }
    
    for (int i=0; i<6; ++i) {
        m_data[k++] = m_normal[4*i+0].x;
        m_data[k++] = m_normal[4*i+0].y;
        m_data[k++] = m_normal[4*i+0].z;
        
        m_data[k++] = m_normal[4*i+1].x;
        m_data[k++] = m_normal[4*i+1].y;
        m_data[k++] = m_normal[4*i+1].z;
        
        m_data[k++] = m_normal[4*i+2].x;
        m_data[k++] = m_normal[4*i+2].y;
        m_data[k++] = m_normal[4*i+2].z;
        
        m_data[k++] = m_normal[4*i+0].x;
        m_data[k++] = m_normal[4*i+0].y;
        m_data[k++] = m_normal[4*i+0].z;
        
        m_data[k++] = m_normal[4*i+2].x;
        m_data[k++] = m_normal[4*i+2].y;
        m_data[k++] = m_normal[4*i+2].z;
        
        m_data[k++] = m_normal[4*i+3].x;
        m_data[k++] = m_normal[4*i+3].y;
        m_data[k++] = m_normal[4*i+3].z;
    }

    for (int i=0; i<6; ++i) {
        m_data[k++] = m_texCoord[4*i+0].x;
        m_data[k++] = m_texCoord[4*i+0].y;
        
        m_data[k++] = m_texCoord[4*i+1].x;
        m_data[k++] = m_texCoord[4*i+1].y;
        
        m_data[k++] = m_texCoord[4*i+2].x;
        m_data[k++] = m_texCoord[4*i+2].y;
        
        m_data[k++] = m_texCoord[4*i+0].x;
        m_data[k++] = m_texCoord[4*i+0].y;
        
        m_data[k++] = m_texCoord[4*i+2].x;
        m_data[k++] = m_texCoord[4*i+2].y;
        
        m_data[k++] = m_texCoord[4*i+3].x;
        m_data[k++] = m_texCoord[4*i+3].y;
    }
    
    for (int i=0; i<6; ++i) {
        m_data[k++] = m_color[4*i+0].r;
        m_data[k++] = m_color[4*i+0].g;
        m_data[k++] = m_color[4*i+0].b;
        m_data[k++] = m_color[4*i+0].a;
        
        m_data[k++] = m_color[4*i+1].r;
        m_data[k++] = m_color[4*i+1].g;
        m_data[k++] = m_color[4*i+1].b;
        m_data[k++] = m_color[4*i+1].a;
        
        m_data[k++] = m_color[4*i+2].r;
        m_data[k++] = m_color[4*i+2].g;
        m_data[k++] = m_color[4*i+2].b;
        m_data[k++] = m_color[4*i+2].a;
        
        m_data[k++] = m_color[4*i+0].r;
        m_data[k++] = m_color[4*i+0].g;
        m_data[k++] = m_color[4*i+0].b;
        m_data[k++] = m_color[4*i+0].a;
        
        m_data[k++] = m_color[4*i+2].r;
        m_data[k++] = m_color[4*i+2].g;
        m_data[k++] = m_color[4*i+2].b;
        m_data[k++] = m_color[4*i+2].a;
        
        m_data[k++] = m_color[4*i+3].r;
        m_data[k++] = m_color[4*i+3].g;
        m_data[k++] = m_color[4*i+3].b;
        m_data[k++] = m_color[4*i+3].a;
    }
}

