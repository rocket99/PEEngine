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
#include "PEMath.h"
#include "PENode.h"
#include "PEPrefix.h"

class PELayer3D: public PENode
{
public:
    static PELayer3D *create(const Size3D &size);
    virtual bool initWithSize(const Size3D &size);
    
    void draw();
    PECamera *getCamera();
protected:
    PELayer3D();
    ~PELayer3D();
    
private:
    Size3D m_size;
    PECamera *m_camera;
};

#endif /* defined(__Engine__PELayer__) */
