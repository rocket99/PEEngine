//
//  PELine.h
//  Engine
//
//  Created by rocket99 on 14-9-17.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PELine__
#define __Engine__PELine__

#include <iostream>
#include "PEDataType.h"

class PELine2D
{
public:
    
    enum LineSide{
        Line_Left_Side,
        Line_Right_Side,
        In_Line,
    };
    
    PELine2D();
    ~PELine2D();
    PELine2D(const P2D &A, const P2D &B);
    PELine2D(float px, float py, float pc);
    PELine2D(const PELine2D &line);//拷贝构造函数
    
    LineSide PointAtWhichSide(const P2D &C);
    
    float slope();
    float intercept();
    P3D parameters();
    
    float slope() const;
    float intercept() const;
    P3D parameters() const;
    
    friend P2D CrossPoint(const PELine2D &A, const PELine2D &B);
    float distance(const P2D &P);
    
    PELine2D verticalLineAtPoint(const P2D &P);
    
private:
    float m_Px, m_Py, m_Pc; //m_Px*x + m_Py*y + m_Pc = 0.0;
    P2D m_A, m_B;
};


// (x+a)/A = (y+b)/B = (z+c)/C = t;
class PELine3D
{
public:
    PELine3D(const P3D &oft, const P3D &slope, float t);
    ~PELine3D();

private:
    float m_oftx, m_ofty, m_oftz;
    float m_dx, m_dy, m_dz;
    float m_const;
};
#endif /* defined(__Engine__PELine__) */
