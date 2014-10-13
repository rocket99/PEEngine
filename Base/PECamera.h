//
//  PECamera.h
//  Engine
//
//  Created by rocket99 on 14-8-25.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PECamera__
#define __Engine__PECamera__

#include <iostream>
#include "PEMatrix.h"
#include "PEDataType.h"

class PECamera:public PEMatrix
{
public:
    static PECamera *getInstance();
    static void purge();
    PECamera();
    ~PECamera();
    static PECamera *create(const P3D &world, const P3D &pos, const P3D &focus, const V3D &up);
    bool init(const P3D &world, const P3D &pos, const P3D &focus, const P3D &up);
    
    P3D &World(){ return m_worldSize; };
    P3D &WorldPos(){ return  m_worldPos; };
    P3D &WorldFocus(){ return m_worldFocus;};
    P3D &upDirect(){ return m_up; };
    
    void setPerspect(float fovy, float aspect, float zNear, float zFar);
    float &fovy();
    float &aspect();
    float &zNear();
    float &zFar();
    
    PEMatrix modelViewProject();
    PEMatrix modelViewOrtho(float left, float right, float bottom, float top, float front, float back);
    
    //运动
    void move(const P3D &delta);
    void move(float dx, float dy, float dz);
    void roll(float angle);
    void pitch(float angle);
    void yaw(float angle);
    
private:
    void normalized();
    void setMatrixData();
    
    P3D m_worldPos, m_worldSize, m_worldFocus;
    P3D m_pos, m_center, m_up;
    V3D nx, ny, nz;
    
    PEMatrix *m_perspect;
    float m_fovy, m_aspect, m_zNear, m_zFar;
    void setPerspectMatrix();
};

#endif /* defined(__Engine__PECamera__) */
