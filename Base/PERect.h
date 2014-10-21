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
#include "PEPolygonNode.h"
#include "../PETexture.h"

class PERect:public PEPolygonNode
{
public:
    PERect();
    ~PERect();
    
    static PERect *create(float width, float height);
    bool initWithSize(float width, float height);
    void draw();
    void drawFBO();
protected:
    float m_width, m_height;
    float *m_data;
    void drawFunc();
};

#endif /* defined(__Engine__PERect__) */


