//
//  PEFbxModel.cpp
//  Engine
//
//  Created by rocket99 on 14-9-18.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEFbxModel.h"

PEModelFBX *PEModelFBX::createWithFBX(const char *fileName)
{
    PEModelFBX *model = new PEModelFBX();
    if(model->initWithFBX(fileName)){
        return model;
    }
    delete model;
    return NULL;
}

bool PEModelFBX::initWithFBX(const char *fileName)
{
    if(!PERealNode::init()){
        return false;
    }
    
    FbxManager *lSdkManager = FbxManager::Create();
    FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);
    
    FbxImporter *lImporter = FbxImporter::Create(lSdkManager, "");
    bool lImportStatus = lImporter->Initialize(fileName, -1, lSdkManager->GetIOSettings());
    if(!lImportStatus){
        PELog("fbx error:%s", lImporter->GetStatus().GetErrorString());
        return false;
    }
    FbxScene *pScene = FbxScene::Create(lSdkManager, "myScene");
    lImporter->Import(pScene);
    
    FbxNode *rootNode = pScene->GetRootNode();
    
    FbxDouble3 pos = rootNode->LclTranslation.Get();
    FbxDouble3 rotation = rootNode->LclRotation.Get();
    FbxDouble3 scale = rootNode->LclScaling.Get();
    
    
    
    this->processNodeInfo(rootNode);
    return true;
}

void PEModelFBX::processNodeInfo(FbxNode *node)
{
    if (node == NULL) {
        return;
    }
    const char *nodeName = node->GetName();
    FbxDouble3 translation = node->LclTranslation.Get();
    FbxDouble3 rotation = node->LclRotation.Get();
    FbxDouble3 scaling = node->LclScaling.Get();
    
    printf("<node name= %s>\n\t<translation=(%.3f, %.3f, %.3f)>\n\
           <rotation=(%.3f, %.3f, %.3f)>\n\t<scale = (%.3f, %.3f, %.3f)>\n",
           nodeName,
           translation[0], translation[1], translation[2],
           rotation[0], rotation[1], rotation[2],
           scaling[0], scaling[1], scaling[2]);
    
    FbxNodeAttribute *attribute = node->GetNodeAttribute();
    if(NULL != attribute){
        switch (attribute->GetAttributeType()) {
            case FbxNodeAttribute::eUnknown:
                
                break;
            case FbxNodeAttribute::eNull:
                
                break;
            case FbxNodeAttribute::eMarker:
                
                break;
            case FbxNodeAttribute::eSkeleton:
                printf("sleleton obj\n");
                break;
            case FbxNodeAttribute::eMesh:
                printf("mesh obj\n");
                break;
            case FbxNodeAttribute::eNurbs:
                
                break;
            case FbxNodeAttribute::ePatch:
                
                break;
            case FbxNodeAttribute::eCamera:
                printf("camera obj\n");
                break;
            case FbxNodeAttribute::eCameraStereo:
                
                break;
            case FbxNodeAttribute::eCameraSwitcher:
                
                break;
            case FbxNodeAttribute::eLight:
                printf("light obj\n");
                break;
            case FbxNodeAttribute::eOpticalReference:
                
                break;
            case FbxNodeAttribute::eOpticalMarker:
                
                break;
            case FbxNodeAttribute::eNurbsCurve:
                
                break;
            case FbxNodeAttribute::eTrimNurbsSurface:
                
                break;
            case FbxNodeAttribute::eBoundary:
                
                break;
            case FbxNodeAttribute::eNurbsSurface:
                
                break;
            case FbxNodeAttribute::eShape:
                
                break;
            case FbxNodeAttribute::eLODGroup:
                
                break;
            case FbxNodeAttribute::eSubDiv:
                
                break;
            case FbxNodeAttribute::eCachedEffect:
                
                break;
            case FbxNodeAttribute::eLine:
                
                break;
            default:
                break;
        }
    }else{
        printf("------\n");
    }
    for (int i=0; i<node->GetChildCount(); ++i) {
        this->processNodeInfo(node->GetChild(i));
    }
}