//
//  PEPolygon.h
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEPolygon__
#define __Engine__PEPolygon__

#include <iostream>
#include "PENode.h"

class PEPolygon:public PENode
{
public:
    PEPolygon();
    ~PEPolygon();
    static PEPolygon *createWithPoints(P2D *points, int num);
    bool initWithPoints(P2D *points, int num);
    virtual void draw();
private:
    float *m_data;
    int m_num;
};
#endif /* defined(__Engine__PEPolygon__) */
