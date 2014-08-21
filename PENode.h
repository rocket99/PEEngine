//
//  PENode.h
//  Engine
//
//  Created by rocket99 on 14-8-20.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PENode__
#define __Engine__PENode__

#include "PEObject.h"
#include "PEPrefix.h"
#include "PEDataType.h"
#include "PEMatrix.h"
#include "PEVector.h"

class PENode:public PEObject
{
public:
    static PENode *create();
    bool init();
    
    void setTag(int value);
    int getTag();
    
    void addChild(PENode *node);
    void addChild(PENode *node, int tag);
    void removeFromParentNode();
    
    void setParentNode(PENode *node);
    PENode *getParentNode();
    
    virtual void draw();
    
    void setGLProgram(GLuint prog);
    GLuint getGLProgram();
protected:
    PENode();
    ~PENode();
    
    P3D m_posiiton;
    PEMatrix m_rotate;
    GLuint m_program;
private:
    PENode *m_parent;
    std::vector<PENode *> m_children;
    int m_tag;
};

#endif /* defined(__Engine__PENode__) */

