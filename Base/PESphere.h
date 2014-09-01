//
//  PESphere.h
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PESphere__
#define __Engine__PESphere__

#include <iostream>
#include "PEMeshSurface.h"

class PESphere:public PEMeshSurface
{
public:
    PESphere();
    ~PESphere();
    static PESphere *create(int row, int col, float radius);
    bool initWithRadius(int row, int col, int radius);
private:
    float m_radius;
    float *m_data;
    
    void setNormalData();
    void setCoordData();
};
#endif /* defined(__Engine__PESphere__) */
