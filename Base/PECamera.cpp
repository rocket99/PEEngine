//
//  PECamera.cpp
//  Engine
//
//  Created by rocket99 on 14-8-25.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PECamera.h"


PECamera::PECamera()
{
    m_up = Point3D(0.0, 1.0, 0.0);
    m_center = Point3D(0.0, 0.0, 0.0);
    m_pos = Point3D(0.0, 0.0, 1.0);
    m_camera = NULL;
    m_perspect = NULL;
}

PECamera::~PECamera()
{
    delete m_perspect;
}

PECamera *PECamera::create(const P3D &world, const P3D &pos, const P3D &focus, const V3D &up)
{
    PECamera *camera = new PECamera();
    if(camera->init(world, pos, focus, up)){
        camera->autoRelease();
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
    m_camera = new PEMatrix(4, 4);
    m_perspect = new PEMatrix(4, 4);
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
    ny = m_up.normal();
    
    nx = cross(nz, ny).normal();
    ny = cross(nx, nz).normal();
    m_up = ny;
}

void PECamera::setMatrixData()
{
    
    this->normalized();
    m_camera->Elm(0, 0) = nx.x;  m_camera->Elm(0, 1) = nx.y;
    m_camera->Elm(0, 2) = nx.z;  m_camera->Elm(0, 3) = -dot(nx, m_pos);
    m_camera->Elm(1, 0) = ny.x;  m_camera->Elm(1, 1) = ny.y;
    m_camera->Elm(1, 2) = ny.z;  m_camera->Elm(1, 3) = -dot(ny, m_pos);
    m_camera->Elm(2, 0) = -nz.x; m_camera->Elm(2, 1) = -nz.y;
    m_camera->Elm(2, 2) = -nz.z; m_camera->Elm(2, 3) = dot(nz, m_pos);
    m_camera->Elm(3, 0) = m_camera->Elm(3, 1) = m_camera->Elm(3, 2) = 0.0f;
    m_camera->Elm(3, 3) = 1.0f;
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
    float sa = sin(0.5*m_fovy/180.0*M_PI);
    float ca = cos(0.5*m_fovy/180.0*M_PI);
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
    return cross(*m_perspect, *m_camera);
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
    return cross(mat, *m_camera);
}

void PECamera::move(const P3D &delta)
{
    m_worldFocus += delta.x*nx+delta.y*ny+delta.z*nz;
    m_worldPos   += delta.x*nx+delta.y*ny+delta.z*nz;
    this->normalized();
}

void PECamera::move(float dx, float dy, float dz)
{
    m_worldPos += Point3D(dx, dy, dz);
    m_worldFocus += Point3D(dx, dy, dz);
    this->normalized();
}

void PECamera::roll(float angle)
{
    PEMatrix mat = PEMatrix::RotationMatrix(nz, angle);
    PEMatrix mat_x(4, 1), mat_y(4, 1);
    mat_x.Elm(0, 0) = nx.x; mat_x.Elm(1, 0) = nx.y;
    mat_x.Elm(2, 0) = nx.z; mat_x.Elm(3, 0) = 0.0;
    mat_y.Elm(0, 0) = ny.x; mat_y.Elm(1, 0) = ny.y;
    mat_y.Elm(2, 0) = ny.z; mat_y.Elm(3, 0) = 0.0;
    
    PEMatrix X = cross(mat, mat_x);
    PEMatrix Y = cross(mat, mat_y);
    
    nx = Point3D(X.Elm(0, 0), X.Elm(1, 0), X.Elm(2, 0));
    ny = Point3D(Y.Elm(0, 0), Y.Elm(1, 0), Y.Elm(2, 0));
    m_up = ny;
}

void PECamera::pitch(float angle)
{
    PEMatrix mat = PEMatrix::RotationMatrix(nx, angle);
    PEMatrix mat_z(4, 1), mat_y(4, 1);
    mat_z.Elm(0, 0) = nz.x; mat_z.Elm(1, 0) = nz.y;
    mat_z.Elm(2, 0) = nz.z; mat_z.Elm(3, 0) = 1.0;
    mat_y.Elm(0, 0) = ny.x; mat_y.Elm(1, 0) = ny.y;
    mat_y.Elm(2, 0) = ny.z; mat_y.Elm(3, 0) = 1.0;
    
    PEMatrix Z = cross(mat, mat_z);
    PEMatrix Y = cross(mat, mat_y);
    nz = Point3D(Z.Elm(0, 0), Z.Elm(1, 0), Z.Elm(2, 0)).normal();
    ny = Point3D(Y.Elm(0, 0), Y.Elm(1, 0), Y.Elm(2, 0)).normal();
    m_up = ny;
    m_worldFocus = m_worldPos + (m_worldFocus-m_worldPos).morel()*nz;
    this->normalized();
}

void PECamera::yaw(float angle)
{
    PEMatrix mat = PEMatrix::RotationMatrix(ny, angle);
    PEMatrix mat_z(4, 1), mat_x(4, 1);
    mat_z.Elm(0, 0) = nz.x; mat_z.Elm(1, 0) = nz.y;
    mat_z.Elm(2, 0) = nz.z; mat_z.Elm(3, 0) = 0.0;
    mat_x.Elm(0, 0) = nx.x; mat_x.Elm(1, 0) = nx.y;
    mat_x.Elm(2, 0) = nx.z; mat_x.Elm(3, 0) = 0.0;
    PEMatrix Z = cross(mat, mat_z);
    PEMatrix X = cross(mat, mat_x);
    nz = Point3D(Z.Elm(0, 0), Z.Elm(1, 0), Z.Elm(2, 0)).normal();
    nx = Point3D(X.Elm(0, 0), X.Elm(1, 0), X.Elm(2, 0)).normal();
    m_worldFocus = m_worldPos + (m_worldFocus - m_worldPos).morel()*nz;
    this->normalized();
}




