//
//  PEMeshSurface.cpp
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEMeshSurface.h"

PEMeshSurface::PEMeshSurface():m_row(0),
m_col(0), m_coords(NULL), m_texCoords(NULL),
m_normals(NULL), m_data(NULL), isDataSet(false)
{}

PEMeshSurface::~PEMeshSurface()
{
    if(m_normals != NULL){
        delete [] m_normals;
    }
    if(m_coords != NULL){
        delete [] m_coords;
    }
    if(m_texCoords != NULL){
        delete [] m_texCoords;
    }
    if(m_data != NULL){
        delete [] m_data;
    }
}

PEMeshSurface *PEMeshSurface::create(int row, int col)
{
    PEMeshSurface *obj = new PEMeshSurface();
    if(obj->initWithSize(row, col)){
        obj->autoRelease();
        return obj;
    }
    delete obj;
    return NULL;
}

bool PEMeshSurface::initWithSize(int row, int col)
{
    if(!PERealNode::init()){
        return false;
    }
    m_row = row;
    m_col = col;
    m_coords = new P3D [(m_row+1) * (m_col+1)];
    m_normals = new P3D [(m_row+1) * (m_col+1)];
    m_texCoords = new P2D [(m_row+1) * (m_col+1)];
    
    m_data = new GLfloat[m_row*m_col*6*(3+2+3)];
    return true;
}

void PEMeshSurface::setCoordData()
{
    for (int i=0; i<=m_row; ++i) {
        for (int j=0; j<=m_col; ++j) {
            m_coords[i*(m_col+1)+j] = Point3D((float)j/m_col*100.0-50.0, (float)i/m_row*100.0-50.0, 0.0);
        }
    }
}

void PEMeshSurface::setTexCoordData()
{
    for (int i=0; i<=m_row; ++i) {
        for (int j=0; j<=m_col; ++j) {
            m_texCoords[i*(m_col+1)+j] = Point2D((float)j/m_col, (float)i/m_row);
        }
    }
}

void PEMeshSurface::setNormalData()
{
    for (int i=0; i<=m_row; ++i) {
        for (int j=0; j<=m_col; ++j) {
            m_normals[i*(m_col+1)+j] = Point3D(0.0, 0.0, 1.0);
        }
    }
}

void PEMeshSurface::setDrawData()
{
    if(isDataSet){
        return;
    }
    long k = 0;
    for (int i=0; i<m_row; ++i) {
        for(int j=0; j<m_col; ++j){
            m_data[k++] = m_coords[i*(m_col+1)+j].x;
            m_data[k++] = m_coords[i*(m_col+1)+j].y;
            m_data[k++] = m_coords[i*(m_col+1)+j].z;
            
            m_data[k++] = m_coords[i*(m_col+1)+j+1].x;
            m_data[k++] = m_coords[i*(m_col+1)+j+1].y;
            m_data[k++] = m_coords[i*(m_col+1)+j+1].z;
            
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j].x;
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j].y;
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j].z;
            
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j].x;
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j].y;
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j].z;
         
            m_data[k++] = m_coords[i*(m_col+1)+j+1].x;
            m_data[k++] = m_coords[i*(m_col+1)+j+1].y;
            m_data[k++] = m_coords[i*(m_col+1)+j+1].z;

            m_data[k++] = m_coords[(i+1)*(m_col+1)+j+1].x;
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j+1].y;
            m_data[k++] = m_coords[(i+1)*(m_col+1)+j+1].z;
        }
    }
    for (int i=0; i<m_row; ++i) {
        for(int j=0; j<m_col; ++j){
            m_data[k++] = m_texCoords[i*(m_col+1)+j].x;
            m_data[k++] = m_texCoords[i*(m_col+1)+j].y;
            
            m_data[k++] = m_texCoords[i*(m_col+1)+j+1].x;
            m_data[k++] = m_texCoords[i*(m_col+1)+j+1].y;
            
            m_data[k++] = m_texCoords[(i+1)*(m_col+1)+j].x;
            m_data[k++] = m_texCoords[(i+1)*(m_col+1)+j].y;
            
            m_data[k++] = m_texCoords[(i+1)*(m_col+1)+j].x;
            m_data[k++] = m_texCoords[(i+1)*(m_col+1)+j].y;
            
            m_data[k++] = m_texCoords[i*(m_col+1)+j+1].x;
            m_data[k++] = m_texCoords[i*(m_col+1)+j+1].y;
            
            m_data[k++] = m_texCoords[(i+1)*(m_col+1)+j+1].x;
            m_data[k++] = m_texCoords[(i+1)*(m_col+1)+j+1].y;
        }
    }
    for (int i=0; i<m_row; ++i) {
        for(int j=0; j<m_col; ++j){
            m_data[k++] = m_normals[i*(m_col+1)+j].x;
            m_data[k++] = m_normals[i*(m_col+1)+j].y;
            m_data[k++] = m_normals[i*(m_col+1)+j].z;
            
            m_data[k++] = m_normals[i*(m_col+1)+j+1].x;
            m_data[k++] = m_normals[i*(m_col+1)+j+1].y;
            m_data[k++] = m_normals[i*(m_col+1)+j+1].z;
            
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j].x;
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j].y;
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j].z;
            
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j].x;
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j].y;
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j].z;
            
            m_data[k++] = m_normals[i*(m_col+1)+j+1].x;
            m_data[k++] = m_normals[i*(m_col+1)+j+1].y;
            m_data[k++] = m_normals[i*(m_col+1)+j+1].z;
            
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j+1].x;
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j+1].y;
            m_data[k++] = m_normals[(i+1)*(m_col+1)+j+1].z;
        }
    }
    isDataSet = true;
//    this->setVAO();
}

void PEMeshSurface::update()
{
    this->setDrawData();
}

void PEMeshSurface::draw()
{
    this->update();
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

void PEMeshSurface::drawFBO()
{
    if(!m_isVisible){
        return;
    }
    PENode::drawFBO();
    m_program = m_program0;
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    this->setDrawData();
    glUseProgram(m_program);
    this->setLightProjectViewUniform(UNIFORM_MODELPROJECT);
    this->drawFunc();
}

void PEMeshSurface::drawFunc()
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
    
    loc = glGetUniformLocation(m_program, "u_skyBox");
    if(loc >= 0){
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
        glUniform1i(loc, 0);
    }
    
    this->setMaterialUniformBlock();
    this->setLightUniformBlock();
    
	glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, &m_data[0]);
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, &m_data[m_row*m_col*18]);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glVertexAttribPointer(ATTRIB_NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, &m_data[m_row*m_col*30]);
    glEnableVertexAttribArray(ATTRIB_NORMAL_LOC);
    glDrawArrays(GL_TRIANGLES, 0, m_row*m_col*6);
    glDisableVertexAttribArray(ATTRIB_POINT_LOC);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glDisableVertexAttribArray(ATTRIB_NORMAL_LOC);
 
//	  glBindVertexArray(m_VAO);
//    glDrawArrays(GL_TRIANGLES, 0, m_row*m_col*6);
//    glBindVertexArray(0);
    this->deleteMaterialUbo();
    this->deleteLightUbo();
}

void PEMeshSurface::setVAO()
{
    GLuint pointBuf, normalBuf, texCoordBuf;
    glGenBuffers(1, &pointBuf);
    glBindBuffer(GL_ARRAY_BUFFER, pointBuf);
    glBufferData(GL_ARRAY_BUFFER, m_row*m_col*18*sizeof(GLfloat), &m_data[0], GL_STATIC_DRAW);
    glGenBuffers(1, &normalBuf);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuf);
    glBufferData(GL_ARRAY_BUFFER, 18*m_row*m_col*sizeof(GLfloat), &m_data[m_row*m_col*18],
					GL_STATIC_DRAW);
    glGenBuffers(1, &texCoordBuf);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuf);
    glBufferData(GL_ARRAY_BUFFER, 12*m_row*m_col*sizeof(GLfloat), &m_data[m_row*m_col*12], 
					GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glEnableVertexAttribArray(ATTRIB_NORMAL_LOC);
    
    glBindBuffer(GL_ARRAY_BUFFER, pointBuf);
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuf);
    glVertexAttribPointer(ATTRIB_NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);    
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuf);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL);
    
    glDisableVertexAttribArray(ATTRIB_POINT_LOC);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glDisableVertexAttribArray(ATTRIB_NORMAL_LOC);
}



