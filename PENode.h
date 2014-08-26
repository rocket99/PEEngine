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
#include "PEMath.h"

class PENode:public PEObject
{
public:
    static PENode *create();
    bool init();
    
    void setTag(int value);
    int getTag();
    
    void addChild(PENode *node);
    void addChild(PENode *node, int tag);
    void addChild(PENode *node, string name);
    
    void removeChild(PENode *node);
    void removeChildByTag(int tag);
    void removeChildByName(string name);
    
    void removeFromParentNode();
    
    void setParentNode(PENode *node);
    PENode *getParentNode();
    
    virtual void draw();
    
    void setGLProgram(GLuint prog);
    GLuint getGLProgram();
    
    P3D &Position();
    bool &Visible();
    P3D &World();
    
    Color4F &Color();
    
    void setRotate(V3D axis, float angle);
    
    virtual void update();
protected:
    PENode();
    ~PENode();
    bool m_isVisible;
    P3D m_position;
    PEMatrix m_rotate;
    
    GLuint m_program;
    
    V3D m_worldSize;
    P3D m_worldPos;
    PEMatrix m_worldRotate;
    P3D getWorldPos();
    Color4F m_color;
private:
    PENode *m_parent;
    std::vector<PENode *> m_children;
    int m_tag;
};

#endif /* defined(__Engine__PENode__) */



