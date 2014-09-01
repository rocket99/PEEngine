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
m_normals(NULL)
{}

PEMeshSurface::~PEMeshSurface()
{
    if(m_normals != NULL){
        delete m_normals;
    }
    if(m_coords != NULL){
        delete m_coords;
    }
    if(m_texCoords != NULL){
        delete m_texCoords;
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
    return true;
}


void PEMeshSurface::draw()
{
    
}


