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



