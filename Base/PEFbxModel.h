//
//  PEFbxModel.h
//  Engine
//
//  Created by rocket99 on 14-9-18.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEFbxModel__
#define __Engine__PEFbxModel__

#include <iostream>
#include "PERealNode.h"
#include <fbxsdk.h>

class PEModelFBX:public PERealNode
{
public:
    PEModelFBX();
    ~PEModelFBX();
    
    static PEModelFBX *createWithFBX(const char *fileName);
    bool initWithFBX(const char *fileName);
    
    static PEModelFBX *createWithFbxNode(FbxNode *node);
    bool initWithFbxNode(FbxNode *node);
    
    void draw();
    void drawFBO();

private:
    
    typedef struct polygonData {
        int pointNum;
        P3D *coodinates;
        P3D *normals;
        P2D *uvCoords;
    } Polygon;
    int m_polygonNum;
    Polygon *m_polygonData;
    void deletePolygons();
    
    void processNodeInfo(FbxNode *node);
    void ProcessMeshInfo(FbxNode *node);
    
    void setPolygonData(FbxMesh *mesh);
    int m_triangleNum;
    GLfloat *m_vertData;
    
    void drawFunc();
    
    void setDrawTriangleData();//设置要画的三角形的数据
};

#endif /* defined(__Engine__PEFbxModel__) */
