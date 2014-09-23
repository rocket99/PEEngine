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
#include "../Math/PEMath.h"

class PELayer3D;
class PENode:public PEObject
{
public:
    static PENode *create();
    bool init();
    
    void setTag(int value);
    int getTag();
    
    virtual void addChild(PENode *node);
    virtual void addChild(PENode *node, int tag);
    virtual void addChild(PENode *node, string name);
    
    virtual void removeChild(PENode *node);
    virtual void removeChildByTag(int tag);
    virtual void removeChildByName(string name);
    virtual void removeAllChildern();
    virtual void removeFromParentNode();
    
    PENode * getChildByTag(int tag);
    PENode * getChildByName(string name);
    std::vector<PENode *> &getChildren();
    
    void setParentNode(PENode *node);
    PENode *getParentNode();
    
    virtual void draw();
    virtual void drawFBO();
    
    bool &Visible();
    P3D &Position();
    P3D &World();
    V3D &RotateAxis();
    float &RotateAngle();
    void setRotate(V3D axis, float angle);
    PEMatrix &getRotate();
    
    float &ScaleX();
    float &ScaleY();
    float &ScaleZ();
    P3D &Scale();
    
    virtual void update();
protected:
    PENode();
    ~PENode();
    int m_tag;
    bool m_isVisible;
    P3D m_scale;
    P3D m_position;
    V3D m_worldSize;
    P3D m_worldPos;
    
    void setWorldMat();
    PEMatrix m_worldMat;
    
    V3D m_locRotateAxis;
    float m_locRotateAngle;
    PEMatrix m_localRotate;

    PENode *m_parent;
    std::vector<PENode *> m_children;
};
#endif /* defined(__Engine__PENode__) */



