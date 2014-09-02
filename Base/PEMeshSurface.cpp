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
        return obj;
    }
    delete obj;
    return NULL;
}

bool PEMeshSurface::initWithSize(int row, int col)
{
    if(!PENode::init()){
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
            m_coords[i*(m_col+1)+j] = Point3D(0.0, 0.0, 0.0);
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
}

void PEMeshSurface::draw()
{
    if(glIsProgram(m_program) == GL_FALSE){
        return;
    }
    this->setDrawData();
    GLint loc = glGetUniformLocation(m_program, UNIFORM_SPACE);
    if(loc >= 0){
        glUniform3f(loc, m_worldSize.x, m_worldSize.y, m_worldSize.z);
    }
    loc = glGetUniformLocation(m_program, UNIFORM_SYSMAT);
    if(loc >=0){
        this->setWorldMat();
        glUniformMatrix4fv(loc, 1, GL_FALSE, m_worldMat.getData());
    }
    loc = glGetUniformLocation(m_program, UNIFORM_MODELPROJECT);
    if(loc >=0){
        PEMatrix mat = PECamera::getInstance()->modelViewProject();
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat.getData());
    }
    loc = glGetUniformLocation(m_program, UNIFORM_COLOR);
    if(loc >= 0){
        glUniform4f(loc, m_color.r, m_color.g, m_color.b, m_color.a);
    }
    
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 0, &m_data[0]);
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, &m_data[m_row*m_col*18]);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glVertexAttribPointer(ATTRIB_NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, &m_data[m_row*m_col*30]);
    glEnableVertexAttribArray(ATTRIB_NORMAL_LOC);
    
    glDrawArrays(GL_TRIANGLES, 0, m_row*m_row*6);
}


