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
    
    struct Material{
        Color4F diffuse;
        Color4F ambient;
        Color4F specular;
        Color4F emission;
    };
    
    
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
    void removeAllChildern();
    void removeFromParentNode();
    
    PENode * getChildByTag(int tag);
    PENode * getChildByName(string name);
    
    void setParentNode(PENode *node);
    PENode *getParentNode();
    
    virtual void draw();
    
    virtual void setGLProgram(GLuint prog);
    GLuint getGLProgram();
    
    P3D &Position();
    bool &Visible();
    P3D &World();
    
    Color4F &Color();
    GLuint &Texture();
    
    V3D &RotateAxis();
    float &RotateAngle();
    void setRotate(V3D axis, float angle);
    PEMatrix &getRotate();
    
    virtual void update();
    
    
protected:
    PENode();
    ~PENode();
    
    bool m_isVisible;
    
    P3D m_position;
    GLuint m_program;
    
    V3D m_worldSize;
    P3D m_worldPos;
    
    void setWorldMat();
    PEMatrix m_worldMat;
    
    V3D m_locRotateAxis;
    float m_locRotateAngle;
    PEMatrix m_localRotate;

    GLuint m_texture;
    
    PENode *m_parent;
    std::vector<PENode *> m_children;
    
    int m_tag;
    Color4F m_color;
    
    GLuint m_materialUbo;
    struct Material m_material;
    void setMaterialUniformBlock();
    void deleteMaterialUbo();
private:
    
};

#endif /* defined(__Engine__PENode__) */



