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


// x = At+oftX; y = Bt+ofty; z = Ct+oftz;
class PELine3D
{
public:
    PELine3D(const P3D &A, const P3D &B);//两点确定一直线
    PELine3D(const V3D &direct, float dx, float dy, float dz);//一点一个方向向量确定一条直线
    PELine3D(float dx, float dy, float dz, float oftx, float ofty, float oftz); //参数方程参数定义一条直线
    PELine3D(const PELine3D &line);
    ~PELine3D();
    
    P3D &Offset();
    V3D &Direct();

    const P3D &Offset() const;
    const V3D &Direct() const;
    
    bool isParallelToLine(const PELine3D &line);
    bool isPointOnTheLine(const P3D &P);
    
    PELine3D verticalLineAtPoint(const P3D &P);
private:
    P3D m_oft, m_vec;
};
#endif /* defined(__Engine__PELine__) */
