//
//  PEBox.h
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEBox__
#define __Engine__PEBox__

#include <iostream>
#include "PERect.h"

#define BOX_FRONT   "front"
#define BOX_BACK    "back"
#define BOX_LEFT    "left"
#define BOX_RIGHT   "right"
#define BOX_TOP     "top"
#define BOX_BOTTOM  "bottom"

class PEBox:public PERealNode
{
public:
    PEBox();
    ~PEBox();
    
    static PEBox *createWithSize(const Size3D &size);
    bool initWithSize(const Size3D &size);
    PERect *getBoxSurfaceByName(string name);
    void setGLProgram(GLuint program);
    
    void draw();
private:
    Size3D m_size;
};
#endif /* defined(__Engine__PEBox__) */
