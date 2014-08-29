//
//  PECamera.cpp
//  Engine
//
//  Created by rocket99 on 14-8-25.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PECamera.h"

static PECamera *instance = NULL;

PECamera *PECamera::getInstance()
{
    if (instance == NULL) {
        instance = new PECamera;
    }
    return instance;
}

void PECamera::purge()
{
    if(instance != NULL){
        delete instance;
    }
    instance = NULL;
}

PECamera::PECamera()
{
    m_up = Point3D(0.0, 1.0, 0.0);
    m_center = Point3D(0.0, 0.0, 0.0);
    m_pos = Point3D(0.0, 0.0, 1.0);
    m_row = m_col = 4;
    m_data = (float *)malloc(sizeof(float) * m_row*m_col);
    m_perspect = new PEMatrix(4, 4);
}

PECamera::~PECamera()
{
    delete m_perspect;
}

PECamera *PECamera::create(const P3D &world, const P3D &pos, const P3D &focus, const V3D &up)
{
    PECamera *camera = new PECamera();
    if(camera->init(world, pos, focus, up)){
        return camera;
    }
    delete camera;
    return NULL;
}

bool PECamera::init(const P3D &world, const P3D &pos, const P3D &focus, const P3D &up)
{
    if (pos == focus || isParallel(pos-focus, up) ||  up == Point3D(0.0, 0.0, 0.0)) {
        PELog("pay attention to paramemters such as pos, focus and up, there is some invalid paramemter.\n");
        return false;
    }
    m_worldSize = world;
    m_worldPos = pos;
    m_worldFocus = focus;
    m_up = up;
    this->setMatrixData();
    return true;
}

void PECamera::normalized()
{
    m_up.normalized();
    m_pos = (m_worldPos / m_worldSize);
    m_center = (m_worldFocus / m_worldSize);
    
    nz = (m_center - m_pos).normal();
    ny = m_up;
    nx = cross(nz, ny).normal();
    ny = cross(nx, nz).normal();
    m_up = ny;
}

void PECamera::setMatrixData()
{
    this->normalized();
    Elm(0, 0) = nx.x; Elm(0, 1) = nx.y; Elm(0, 2) = nx.z;
    Elm(0, 3) = -nx.dot(m_pos);
    Elm(1, 0) = ny.x; Elm(1, 1) = ny.y; Elm(1, 2) = ny.z;
    Elm(1, 3) = -ny.dot(m_pos);
    Elm(2, 0) = nz.x; Elm(2, 1) = nz.y; Elm(2, 2) = nz.z;
    Elm(2, 3) = nz.dot(m_pos);
    Elm(3, 0) = Elm(3, 1) = Elm(3, 2) = 0.0f;
    Elm(3, 3) = 1.0f;
}

void PECamera::setPerspect(float fovy, float aspect, float zNear, float zFar){
    m_fovy = fovy; m_aspect = aspect; m_zNear = zNear; m_zFar = zFar;
}

float &PECamera::fovy()
{
    return m_fovy;
}
float &PECamera::aspect()
{
    return m_aspect;
}
float &PECamera::zNear()
{
    return m_zNear;
}
float &PECamera::zFar()
{
    return m_zFar;
}

void PECamera::setPerspectMatrix()
{
    float sa = sin(m_fovy/180.0*M_PI*0.5);
    float ca = cos(m_fovy/180.0*M_PI*0.5);
    m_perspect->Elm(0, 0) = ca/sa/m_aspect;
    m_perspect->Elm(0, 1) = m_perspect->Elm(0, 2) = 0.0;
    m_perspect->Elm(0, 3) = m_perspect->Elm(1, 0) = 0.0;
    m_perspect->Elm(1, 1) = ca/sa;
    m_perspect->Elm(1, 2) = m_perspect->Elm(1, 3) = 0.0;
    m_perspect->Elm(2, 0) = m_perspect->Elm(2, 1) = 0.0;
    m_perspect->Elm(2, 2) = (m_zFar+m_zNear) / (m_zNear-m_zFar);
    m_perspect->Elm(2, 3) = 2.0*m_zNear*m_zFar / (m_zNear - m_zFar);
    
    m_perspect->Elm(3, 0) = m_perspect->Elm(3, 1) = m_perspect->Elm(3, 3) = 0.0;
    m_perspect->Elm(3, 2) = -1.0;
}

PEMatrix PECamera::modelViewProject()
{
    this->setMatrixData();
    this->setPerspectMatrix();
    return cross(*m_perspect, *this);
}

PEMatrix PECamera::modelViewOrtho(float left, float right, float bottom, float top, float near, float far)
{
    PEMatrix mat(4, 4);
    mat.Elm(0, 0) = 2.0/(right-left);
    mat.Elm(0, 1) = 0.0; mat.Elm(0, 2) = 0.0;
    mat.Elm(0, 3) = -(right+left)/(right-left);
    mat.Elm(1, 0) = mat.Elm(1, 2) = 0.0;
    mat.Elm(1, 1) = 2.0/(top-bottom);
    mat.Elm(1, 3) = -(top+bottom)/(top-bottom);
    mat.Elm(2, 0) = mat.Elm(2, 1) = 0.0;
    mat.Elm(2, 2) = 2.0/(near - far);
    mat.Elm(2, 3) = (near+far)/(near-far);
    mat.Elm(3, 0) = mat.Elm(3, 1) = mat.Elm(3, 2) = 0.0;
    mat.Elm(3, 3) = 1.0;
    
    this->setMatrixData();
    return cross(mat, *this);
}


