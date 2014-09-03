//
//  PMCylinder.h
//  Engine
//
//  Created by rocket99 on 14-9-3.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PMCylinder__
#define __Engine__PMCylinder__

#include <iostream>
#include "PEMeshSurface.h"
#include "PEPolarSurface.h"

class PECylinder:public PEMeshSurface
{
public:
    PECylinder();
    ~PECylinder();
    static PECylinder *create(int row, int col, float height, float radius);
    bool initWithParameters(int row, int col, float height, float radius);
    
    void setNormalData();
    void setCoordData();
    
private:
    float m_radius, m_height;
    PEPolarSurface *m_bottom, *m_top;
};
#endif /* defined(__Engine__PMCylinder__) */
