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
    
    friend P2D CrossPoint(const PELine2D &A, const PELine2D &B);
private:
    float m_slope, m_intercept;
    
    P2D m_A, m_B;
};

#endif /* defined(__Engine__PELine__) */
