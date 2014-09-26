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
    static PEModelFBX *createWithFBX(const char *fileName);
    bool initWithFBX(const char *fileName);
    
    static PEModelFBX *createWithFbxNode(FbxNode *node);
    bool initWithFbxNode(FbxNode *node);
    
private:
    void processNodeInfo(FbxNode *node);
    void ProcessMeshInfo(FbxNode *node);
    
    void displayControlPoints(FbxMesh *mesh);
    void displayPolygons(FbxMesh *mesh);
};

#endif /* defined(__Engine__PEFbxModel__) */
