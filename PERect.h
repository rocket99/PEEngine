//
//  PERect.h
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PERect__
#define __Engine__PERect__

#include <iostream>
#include "PENode.h"
#include "PEMath.h"
#include "PEPolygon.h"
#include "PETexture.h"

class PERect:public PEPolygon
{
public:
    PERect();
    ~PERect();
    
    static PERect *create(float width, float height);
    bool initWithSize(float width, float height);
    void draw();
    Color4F &Color();
protected:
    float m_width, m_height;
    float *m_data;
    Color4F m_color;
};

#endif /* defined(__Engine__PERect__) */
