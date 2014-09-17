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
    
    m_slope = (B.y-A.y) / (B.x-A.x);
    PELog("%f", m_slope);
    if (isinf(m_slope)) {
        PELog("m_slope is vertical to axis-x");
    }
    if (isnan(m_slope)) {
        PEWarning("invalid line.");
    }
    m_intercept = (A.y*B.x-A.x*B.y) / (B.x-A.x);
    PELog("intercept:%f", m_intercept);
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

P2D CrossPoint(const PELine2D &A, const PELine2D &B)
{
    return Point2D(0.0, 0.0);
}

