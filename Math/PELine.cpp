//
//  PELine.cpp
//  Engine
//
//  Created by rocket99 on 14-9-17.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PELine.h"
#include "PEVector.h"

PELine2D::PELine2D(){}
PELine2D::~PELine2D(){}
PELine2D::PELine2D(const P2D &A, const P2D &B)
{
    m_A = A;
    m_B = B;
    m_Px = A.x - B.x;
    m_Py = B.y - A.y;
    m_Pc = A.x*B.y - A.y*B.x;
}

PELine2D::PELine2D(float px, float py, float pc)
{
    m_Px = px; m_Py = py; m_Pc = pc;
    if (m_Py == 0.0) {
        m_A = Point2D(-m_Pc/m_Px, 1.0);
        m_B = Point2D(-m_Pc/m_Px, -1.0);
    }else{
        m_A = Point2D(-1.0, (m_Px-m_Pc)/m_Py);
        m_B = Point2D(1.0, -(m_Px+m_Pc)/m_Py);
    }
}

PELine2D::PELine2D(const PELine2D &line)
{
    m_A = line.m_A;
    m_B = line.m_B;
    m_Px = m_A.x - m_B.x;
    m_Py = m_B.y - m_A.y;
    m_Pc = m_A.x*m_B.y - m_A.y*m_B.x;
}

PELine2D::LineSide PELine2D::PointAtWhichSide(const P2D &C)
{
    V2D AC = C - m_A;
    V2D BC = C - m_B;
    float d = AC.x*BC.y - AC.y*BC.x;
    if(d > 0){
        return Line_Left_Side;
    }
    if(d < 0){
        return Line_Right_Side;
    }
    return In_Line;
}

float PELine2D::slope()
{
    return -m_Px/m_Py;
}

float PELine2D::intercept()
{
    return -m_Pc/m_Py;
}

P3D PELine2D::parameters()
{
    return  Point3D(m_Px, m_Py, m_Pc);
}

float PELine2D::slope() const
{
    return -m_Px/m_Py;
}

float PELine2D::intercept() const
{
    return -m_Pc/m_Py;
}

P3D PELine2D::parameters() const
{
    return Point3D(m_Px, m_Py, m_Pc);
}

P2D CrossPoint(const PELine2D &A, const PELine2D &B)
{
    P3D PA = A.parameters();
    P3D PB = B.parameters();
    float a = PA.x*PB.y - PA.y*PB.x;
    return Point2D((PA.y*PB.z-PB.y*PA.z)/a, (PA.z*PB.x-PA.x*PB.z)/a);
}

float PELine2D::distance(const P2D &P)
{
    V2D PA = P-m_A;
    V2D PB = P-m_B;
    float dd = (PA.x *PB.y - PA.y*PB.x)/(m_A-m_B).morel();
    dd = dd > 0.0 ? dd : -dd;
    return dd;
}

PELine2D PELine2D::verticalLineAtPoint(const P2D &P)
{
    PELine2D line;
    line.m_Px = -m_Py;
    line.m_Py =  m_Px;
    line.m_Pc = -(line.m_Px*P.x+line.m_Py*P.y);
    if (m_Py == 0.0) {
        m_A = Point2D(-m_Pc/m_Px, 1.0);
        m_B = Point2D(-m_Pc/m_Px, -1.0);
    }else{
        m_A = Point2D(-1.0, (m_Px-m_Pc)/m_Py);
        m_B = Point2D(1.0, -(m_Px+m_Pc)/m_Py);
    }
    return line;
}


#pragma mark PELine3D
PELine3D::PELine3D(const P3D &oft, const P3D &slope, float t)
{
    m_oftx = oft.x; m_ofty = oft.y; m_oftz = oft.z;
    m_dx = slope.x; m_dy = slope.y; m_dz = slope.z;
    m_const = t;
}




