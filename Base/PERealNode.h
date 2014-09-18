//
//  PERealNode.h
//  Engine
//
//  Created by rocket99 on 14-9-4.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PERealNode__
#define __Engine__PERealNode__

#include <iostream>
#include "PENode.h"
#include "PELayer3D.h"

class PERealNode:public PENode
{
public:
    PERealNode();
    ~PERealNode();
    static PERealNode *create();
    bool init();

    struct Material_Color{
        Color4F diffuse;
        Color4F ambient;
        Color4F specular;
        Color4F emission;
    };
    struct Material_Color &Material();
    
    void setSceneIn(PELayer3D *scene);
    PELayer3D *getSceneIn();
    
    void addChild(PERealNode *node);
    void addChild(PERealNode *node, int tag);
    void addChild(PERealNode *node, string name);
    
    void removeChild(PERealNode *node);
    void removeChildByTag(int tag);
    void removeChildByName(string name);
    void removeAllChildern();
    void removeFromParentNode();
    
    GLuint getCurrentGLProgram();
    
    GLuint &Program0();
    GLuint &Program1();
    
    Color4F &Color();
    GLuint &Texture();
    
protected:
    GLuint m_program0, m_program1;
    GLuint m_program;
    PELayer3D *m_sceneIn;
    
    virtual void setLightUniformBlock();
    virtual void deleteLightUbo();
    
    void setModelViewProjectUniform(string uniform = UNIFORM_MODELPROJECT);
    void setLightProjectViewUniform(string uniform = UNIFORM_LIGHT_CAMERA);
    GLuint m_materialUbo;
    struct Material_Color m_material;
    virtual void setMaterialUniformBlock();
    virtual void deleteMaterialUbo();
    
    void setWorldMatUniform();
    void setSpaceUniform();
    void setColorUniform();
    
    void setDepthTexUnifrom();
    void setTextureUniform();
    Color4F m_color;
    GLuint m_texture;
};
#endif /* defined(__Engine__PERealNode__) */
