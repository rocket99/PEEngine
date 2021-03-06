//
//  PESphereSurface.cpp
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PESphereSurface.h"

PESphereSurface::PESphereSurface()
{
    
}

PESphereSurface::~PESphereSurface()
{
    
}

PESphereSurface *PESphereSurface::create(int row, int col, float radius)
{
    PESphereSurface *sphere = new PESphereSurface;
    if(sphere->initWithRadius(row, col, radius)){
        sphere->autoRelease();
        return sphere;
    }
    delete sphere;
    return NULL;
}

bool PESphereSurface::initWithRadius(int row, int col, int radius)
{
    if(!PEMeshSurface::initWithSize(row, col)){
        return false;
    }
    m_radius = radius;
    this->setCoordData();
    this->setNormalData();
    this->setTexCoordData();
    return true;
}

void PESphereSurface::setCoordData()
{
    for (int i=0; i<=m_row; ++i) {
        for (int j=0; j<=m_col; ++j) {
            m_coords[i*(m_col+1)+j].x = m_radius*sin(M_PI*(float)i/m_row)*cos(2.0*M_PI*(float)(j%m_col)/m_col);
            m_coords[i*(m_col+1)+j].y = m_radius*sin(M_PI*(float)i/m_row)*sin(2.0*M_PI*(float)(j%m_col)/m_col);
            m_coords[i*(m_col+1)+j].z = m_radius*cos(M_PI*(float)i/m_row);
        }
    }
}

void PESphereSurface::setNormalData()
{
    for (int i=0; i<=m_row; ++i) {
        for (int j=0; j<=m_col; ++j) {
            m_normals[i*(m_col+1)+j].x = sin((float)i/m_row*M_PI)*cos((float)(j%m_col)/m_col*M_PI*2.0);
            m_normals[i*(m_col+1)+j].y = sin((float)i/m_row*M_PI)*sin((float)(j%m_col)/m_col*M_PI*2.0);
            m_normals[i*(m_col+1)+j].z = cos((float)i/m_row*M_PI);
        }
    }
}

