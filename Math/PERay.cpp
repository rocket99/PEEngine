//
//  PERay.cpp
//  Engine
//
//  Created by rocket99 on 14-9-16.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PERay.h"

PERay::PERay():
m_origin(Point3D(0.0, 0.0, 0.0)),
m_direction(Point3D(1.0, 0.0, 0.0))
{}

PERay::PERay(const P3D &origin, const V3D &vec)
{
    m_origin = origin;
    m_direction = vec;
}

PERay::~PERay(){}

P3D &PERay::Origin()
{
    return m_origin;
}

V3D &PERay::Direction()
{
    return m_direction;
}

PERay *PERay::getParent()
{
    return m_parent;
}

void PERay::setParent(PERay *ray)
{
    m_parent = ray;
}