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
#include "../Math/PEMath.h"
#include "PENode.h"

class PECamera:public PENode
{
public:
    static PECamera *create(const P3D &world, const P3D &pos, const P3D &focus, const V3D &up);
    bool init(const P3D &world, const P3D &pos, const P3D &focus, const P3D &up);
    
    P3D &World(){ return m_worldSize; };
    P3D &WorldPos(){ return m_worldPos; };
    P3D &WorldFocus(){ return m_worldFocus; };
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
    void roll(float angle = 1.0);
    void pitch(float angle = 1.0);
    void yaw(float angle=1.0);
	
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveForward();
	void moveBackward();

	void lookUp();
	void lookDown();
	void lookLeft();
	void lookRight();
	void positiveRotate();
	void nagitiveRotate();
protected:
    PECamera();
    ~PECamera();
private:
    PEMatrix *m_camera;
    PEMatrix *m_perspect;
    
    void normalized();
    void setMatrixData();
    
    P3D m_worldPos, m_worldSize, m_worldFocus;
    P3D m_pos, m_focus, m_up;
    V3D nx, ny, nz;
    
    float m_fovy, m_aspect, m_zNear, m_zFar;
    void setPerspectMatrix();
};

#endif /* defined(__Engine__PECamera__) */
