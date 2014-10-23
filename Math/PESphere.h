//
//  PESphere.h
//  Engine
//
//  Created by rocket99 on 14/10/20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PESphere__
#define __Engine__PESphere__

#include <stdio.h>
#include "PEDataType.h"
#include "PELine.h"
#include "PEPlane.h"

class PESphere
{
public:
    PESphere();
    PESphere(float radius);
    PESphere(float a, float b, float c);
    ~PESphere();
    
    P3D *surfaceVertices(int row, int column);
protected:
    float m_radius_x, m_radius_y, m_radius_z;
};

#endif /* defined(__Engine__PESphere__) */
