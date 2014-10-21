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
    //Euler旋转顺序
    enum EulerOrder{
        Euler_XYZ,
        Euler_YZX,
        Euler_ZXY,
        Euler_XZY,
        Euler_ZYX,
        Euler_YXZ,
    };
    
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
    
    void Rotate(V3D axis, float angle);
    void setRotate(P3D EulerAngle, EulerOrder order);
    P3D &EulerRotate();
    PEMatrix &RotateMatrix();
    
    float &ScaleX();
    float &ScaleY();
    float &ScaleZ();
    P3D &Scale();
    
    virtual void update();
    
    void blurMotionEnable(bool enable){
        m_blur = enable;
    }
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
    
    EulerOrder m_eOrder;
    V3D m_locEuler;
    PEMatrix m_localRotate;

    PENode *m_parent;
    std::vector<PENode *> m_children;
    
    bool m_blur;
    P3D m_blurPos[10];
};
#endif /* defined(__Engine__PENode__) */



