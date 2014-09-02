//
//  PESphere.cpp
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PESphere.h"

PESphere::PESphere()
{
    
}

PESphere::~PESphere()
{
    
}

PESphere *PESphere::create(int row, int col, float radius)
{
    PESphere *sphere = new PESphere;
    if(sphere->initWithRadius(row, col, radius)){
        return sphere;
    }
    delete sphere;
    return NULL;
}

bool PESphere::initWithRadius(int row, int col, int radius)
{
    if(!PEMeshSurface::initWithSize(row, col)){
        return false;
    }
    this->setCoordData();
    this->setNormalData();
    this->setTexCoordData();
    return true;
}

void PESphere::setCoordData()
{
    for (int i=0; i<=m_row; ++i) {
        for (int j=0; j<=m_col; ++j) {
            m_coords[i*(m_col+1)+j].x = m_radius*sin((float)i/m_row*M_PI)*cos((float)j/m_col*M_PI*2.0);
            m_coords[i*(m_col+1)+j].y = m_radius*sin((float)i/m_row*M_PI)*sin((float)j/m_col*M_PI*2.0);
            m_coords[i*(m_col+1)+j].z = m_radius*cos((float)i/m_row*M_PI);
        }
    }
}

void PESphere::setNormalData()
{
    for (int i=0; i<m_row; ++i) {
        for (int j=0; j<m_col; ++j) {
            m_normals[i*(m_col+1)+j].x = sin((float)i/m_row*M_PI)*cos((float)j/m_col*M_PI*2.0);
            m_normals[i*(m_col+1)+j].y = sin((float)i/m_row*M_PI)*sin((float)j/m_col*M_PI*2.0);
            m_normals[i*(m_col+1)+j].z = cos((float)i/m_row*M_PI);
        }
    }
}


