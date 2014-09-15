//
//  PEMeshSurface.h
//  Engine
//
//  Created by rocket99 on 14-9-1.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEMeshSurface__
#define __Engine__PEMeshSurface__

#include "../PEPrefix.h"
#include "../Math/PEMath.h"
#include "PERealNode.h"

class PEMeshSurface:public PERealNode
{
public:
    PEMeshSurface();
    ~PEMeshSurface();
    static PEMeshSurface *create(int row, int col);
    bool initWithSize(int row, int col);
    virtual void draw();
    virtual void drawFBO();
protected:
    bool isDataSet;
    void setDrawData();
    
    virtual void setNormalData();
    virtual void setCoordData();
    virtual void setTexCoordData();
    int m_row, m_col;
    P3D *m_coords;
    P3D *m_normals;
    P2D *m_texCoords;
    GLfloat *m_data;
    
    void drawFunc();
};
#endif /* defined(__Engine__PEMeshSurface__) */


