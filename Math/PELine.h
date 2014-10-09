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
    LineSide PointAtWhichSide(const P2D &C);
    
    float slope();
    float intercept();
    P3D parameters();
    
    float slope() const;
    float intercept() const;
    P3D parameters() const;
    
    friend P2D CrossPoint(const PELine2D &A, const PELine2D &B);
    
private:
    float m_Px, m_Py, m_Pc; //m_Px*x + m_Py*y + m_Pc = 0.0;
    P2D m_A, m_B;
};

#endif /* defined(__Engine__PELine__) */
