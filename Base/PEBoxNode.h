//
//  PEBoxNode.h
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEBoxNode__
#define __Engine__PEBoxNode__

#include <iostream>
#include "PERect.h"

#define BOX_FRONT   "front"
#define BOX_BACK    "back"
#define BOX_LEFT    "left"
#define BOX_RIGHT   "right"
#define BOX_TOP     "top"
#define BOX_BOTTOM  "bottom"

class PEBoxNode:public PERealNode
{
public:
    PEBoxNode();
    ~PEBoxNode();
    
    static PEBoxNode *createWithSize(const Size3D &size);
    bool initWithSize(const Size3D &size);
    PERect *getBoxSurfaceByName(string name);
    
    void setGLProgram0(GLuint program);
    void setGLProgram1(GLuint program);
    
    void draw();
    void drawFBO();
    void drawFunc();
private:
    Size3D m_size;
    P3D *m_coords;
    P3D *m_normal;
    P2D *m_texCoord;
    Color4F *m_color;
    GLfloat *m_data;
    void initFrontRect();
    void initBackRect();
    void initLeftRect();
    void initRightRect();
    void initTopRect();
    void initBottomRect();
    void updateData();
};
#endif /* defined(__Engine__PEBoxNode__) */
