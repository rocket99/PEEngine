//
//  PEPolarSurface.h
//  Engine
//
//  Created by rocket99 on 14-9-3.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEPolarSurface__
#define __Engine__PEPolarSurface__

#include <iostream>
#include "PEMeshSurface.h"

class PEPolarSurface:public PEMeshSurface
{
public:
    PEPolarSurface();
    ~PEPolarSurface();
    static PEPolarSurface *create(int row, int col, float radius, float delta_h = 0.0);
    bool initWithParmeters(int row, int col, float radius, float delta_h = 0.0);
protected:
    virtual void setNormalData();
    virtual void setCoordData();
    virtual void setTexCoordData();
private:
    float m_height;
    float m_radius;
};
#endif /* defined(__Engine__PEPolarSurface__) */
