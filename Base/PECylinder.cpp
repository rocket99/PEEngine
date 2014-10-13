//
//  PMCylinder.cpp
//  Engine
//
//  Created by rocket99 on 14-9-3.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PECylinder.h"

PECylinder::PECylinder():m_top(nullptr), m_bottom(nullptr)
{}

PECylinder::~PECylinder(){}

PECylinder *PECylinder::create(int row, int col, float height, float radius)
{
    PECylinder *cylinder = new PECylinder;
    if(cylinder->initWithParameters(row, col, height, radius)){
        cylinder->autoRelease();
        return cylinder;
    }
    delete cylinder;
    return NULL;
}

bool PECylinder::initWithParameters(int row, int col, float height, float radius)
{
    if(!PEMeshSurface::initWithSize(row, col)){
        return false;
    }
    m_height = height;
    m_radius = radius;
    this->setCoordData();
    this->setNormalData();
    this->setTexCoordData();
    
    m_bottom = PEPolarSurface::create(2, m_col, m_radius, 0.0);
    m_bottom->Rotate(Point3D(1.0, 0.0, 0), 180.0);
    m_bottom->Position() = Point3D(0.0, 0.0, -0.5*m_height);
    this->addChild(m_bottom);
    
    m_top = PEPolarSurface::create(2, m_col, m_radius, 0.0);
    m_top->Position() = Point3D(0.0, 0.0, 0.5*m_height);
    this->addChild(m_top);
    
    return true;
}

void PECylinder::setNormalData()
{
    for (int i=0; i<=m_row; ++i) {
        for(int j=0; j<=m_col; ++j){
            m_normals[i*(m_col+1)+j].x = cos((float)j/m_col*M_PI*2.0);
            m_normals[i*(m_col+1)+j].y = sin((float)j/m_col*M_PI*2.0);
            m_normals[i*(m_col+1)+j].z = 0.0;
        }
    }
}

void PECylinder::setCoordData()
{
    for(int i=0; i<=m_row; ++i){
        for(int j=0; j<=m_col; ++j){
            m_coords[i*(m_col+1)+j].x = m_radius*cos((float)j/m_col*M_PI*2.0);
            m_coords[i*(m_col+1)+j].y = m_radius*sin((float)j/m_col*M_PI*2.0);
            m_coords[i*(m_col+1)+j].z = -0.5*m_height+(float)i/m_row*m_height;
        }
    }
}

void PECylinder::draw()
{
    PEMeshSurface::draw();
    m_top->Program1() = m_program1;
    m_bottom->Program1() = m_program1;
    m_top->draw();
    m_bottom->draw();
}

void PECylinder::drawFBO()
{
    PEMeshSurface::drawFBO();
    m_top->Program0() = m_program0;
    m_bottom->Program0() = m_program0;
    m_top->drawFBO();
    m_bottom->drawFBO();
}

PEPolarSurface *PECylinder::TopSurface()
{
    return m_top;
}

PEPolarSurface *PECylinder::BottomSurface()
{
    return m_bottom;
}

