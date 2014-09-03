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
            m_coords[i*(m_col+1)+j].x = m_radius *cos((float)j/m_col*M_PI*2.0);
            m_coords[i*(m_col+1)+j].y = m_radius *sin((float)j/m_col*M_PI*2.0);
            m_coords[i*(m_col+1)+j].z = (float)i/m_row * m_height;
        }
    }
}

void PEPolarSurface::setTexCoordData()
{
    PEMeshSurface::setTexCoordData();
}
