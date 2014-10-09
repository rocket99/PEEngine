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

