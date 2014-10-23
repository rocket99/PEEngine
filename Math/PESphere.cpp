//
//  PESphere.cpp
//  Engine
//
//  Created by rocket99 on 14/10/20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PESphere.h"

PESphere::PESphere()
{
    m_radius_x = m_radius_y = m_radius_z = 1.0;
}

PESphere::PESphere(float radius)
{
    m_radius_x = m_radius_y = m_radius_z = radius;
}

PESphere::PESphere(float a, float b, float c)
{
    m_radius_x = a;
    m_radius_y = b;
    m_radius_z = c;
}

PESphere::~PESphere()
{
    
}

P3D *PESphere::surfaceVertices(int row, int column)
{
    if(row <= 0 || column == 0){
        return NULL;
    }
    P3D *vertices = new P3D[(row+1)*(column+1)];
    for (int i=0; i<=row; ++i) {
        for (int j=0; j<=column; ++j) {
            
        }
    }
    return vertices;
}


