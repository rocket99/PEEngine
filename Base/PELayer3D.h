//
//  PELayer.h
//  Engine
//
//  Created by rocket99 on 14-8-22.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PELayer__
#define __Engine__PELayer__

#include <iostream>
#include "../Math/PEMath.h"
#include "PELight.h"
#include "PENode.h"

class PELayer3D: public PENode
{
public:
    static PELayer3D *create(const Size3D &size);
    virtual bool initWithSize(const Size3D &size);
    
    void drawFBO();
    void draw();
    PECamera *getCamera();
    PELight *getLightSource();
    
    void addChild(PENode *node);
    void addChild(PENode *node, int tag);
    void addChild(PENode *node, string name);
    
    void removeChild(PENode *node);
    void removeChildByTag(int tag);
    void removeChildByName(string name);
    void removeAllChildern();
    
protected:
    PELayer3D();
    ~PELayer3D();
    
    Size3D m_size;
    PECamera *m_camera;
    PELight *m_light;
};

#endif /* defined(__Engine__PELayer__) */
