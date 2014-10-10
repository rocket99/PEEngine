//
//  PEPolarSurface.cpp
//  Engine
//
//  Created by rocket99 on 14-9-3.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEPolarSurface.h"

PEPolarSurface::PEPolarSurface()
{
    m_height = 0.0;
    m_radius = 0.0;
}

PEPolarSurface::~PEPolarSurface()
{
    
}

PEPolarSurface *PEPolarSurface::create(int row, int col, float radius, float delta_h/* = 0.0*/)
{
    PEPolarSurface *surface = new PEPolarSurface;
    if(surface->initWithParmeters(row, col, radius, delta_h)){
        surface->autoRelease();
        return surface;
    }
    delete surface;
    return NULL;
}

bool PEPolarSurface::initWithParmeters(int row, int col, float radius, float delta_h /*= 0.0*/)
{
    if(!PEMeshSurface::initWithSize(row, col)){
        return false;
    }
    m_radius = radius;
    m_height = delta_h;
    this->setNormalData();
    this->setCoordData();
    this->setTexCoordData();
    return true;
}

void PEPolarSurface::setNormalData()
{
    for (int i=0; i<=m_row; ++i) {
        for(int j=0; j<=m_col; ++j){
            m_normals[i*(m_col+1)+j].x = 0.0;
            m_normals[i*(m_col+1)+j].y = 0.0;
            m_normals[i*(m_col+1)+j].z = 1.0;
        }
    }
}

void PEPolarSurface::setCoordData()
{
    for(int i=0; i<=m_row; ++i){
        for(int j=0; j<=m_col; ++j){
            m_coords[i*(m_col+1)+j].x = m_radius*i/m_row *cos(2.0*M_PI*(float)j/m_col);
            m_coords[i*(m_col+1)+j].y = m_radius*i/m_row *sin(2.0*M_PI*(float)j/m_col);
            m_coords[i*(m_col+1)+j].z = m_height*(float)i/m_row;
        }
    }
}

void PEPolarSurface::setTexCoordData()
{
    PEMeshSurface::setTexCoordData();
}
