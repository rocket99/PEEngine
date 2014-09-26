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
    EFbxRotationOrder lRotationOrder;
    rootNode->GetRotationOrder(FbxNode::eSourcePivot, lRotationOrder);
    switch (lRotationOrder) {
        case FbxEuler::eOrderXYZ:
            
            break;
        case FbxEuler::eOrderXZY:
            
            break;
        case FbxEuler::eOrderYXZ:
            
            break;
        case FbxEuler::eOrderYZX:
            
            break;
        case FbxEuler::eOrderZXY:
            
            break;
        case FbxEuler::eOrderZYX:
            
            break;
        case FbxEuler::eOrderSphericXYZ:
            
            break;
        default:
            break;
    }
    this->processNodeInfo(rootNode);
    return true;
}

PEModelFBX *PEModelFBX::createWithFbxNode(FbxNode *node)
{
    PEModelFBX *fbx = new PEModelFBX;
    if(fbx->initWithFbxNode(node)){
        return fbx;
    }
    delete fbx;
    return NULL;
}

bool PEModelFBX::initWithFbxNode(FbxNode *node)
{
    if(!PERealNode::init()){
        return false;
    }
    FbxNodeAttribute *attribute = node->GetNodeAttribute();
    if (attribute->GetAttributeType() != FbxNodeAttribute::eMesh) {
        return false;
    }
    this->setName(node->GetName());
    FbxDouble3 pos = node->LclTranslation.Get();
    FbxDouble3 scale = node->LclScaling.Get();
    FbxDouble3 rotation = node->LclRotation.Get();
    m_position = Point3D(pos[0], pos[1], pos[2]);
    P3D Euler = Point3D(rotation[0], rotation[1], rotation[2]);
    m_scale = Point3D(scale[0], scale[1], scale[2]);
    this->setRotate(Euler, PENode::Euler_XYZ);
    
    FbxMesh *mesh = node->GetMesh();
//    this->displayControlPoints(mesh);
    this->displayPolygons(mesh);
    
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
    
    printf("<node name= %s>\n\t<translation=(%.3f, %.3f, %.3f)>\n\t<rotation=(%.3f, %.3f, %.3f)>\n\t<scale = (%.3f, %.3f, %.3f)>\n",
           nodeName,
           translation[0], translation[1], translation[2],
           rotation[0], rotation[1], rotation[2],
           scaling[0], scaling[1], scaling[2]);
    
    FbxNodeAttribute *attribute = node->GetNodeAttribute();
    if(NULL != attribute){
        switch (attribute->GetAttributeType()) {
            case FbxNodeAttribute::eUnknown:
                printf("unknown obj\n");
                break;
            case FbxNodeAttribute::eNull:
                printf("null obj\n");
                break;
            case FbxNodeAttribute::eMarker:
                printf("marker obj\n");
                break;
            case FbxNodeAttribute::eSkeleton:
                printf("sleleton obj\n");
                break;
            case FbxNodeAttribute::eMesh:
                printf("mesh obj\n");
                this->ProcessMeshInfo(node);
                break;
            case FbxNodeAttribute::eNurbs:
                printf("nurbs obj\n");
                break;
            case FbxNodeAttribute::ePatch:
                printf("patch obj\n");
                break;
            case FbxNodeAttribute::eCamera:
                printf("camera obj\n");
                break;
            case FbxNodeAttribute::eCameraStereo:
                printf("camera stereo obj\n");
                break;
            case FbxNodeAttribute::eCameraSwitcher:
                printf("camera switcher obj\n");
                break;
            case FbxNodeAttribute::eLight:
                printf("light obj\n");
                break;
            case FbxNodeAttribute::eOpticalReference:
                printf("optical reference obj\n");
                break;
            case FbxNodeAttribute::eOpticalMarker:
                printf("optical marker obj\n");
                break;
            case FbxNodeAttribute::eNurbsCurve:
                
                break;
            case FbxNodeAttribute::eTrimNurbsSurface:
                
                break;
            case FbxNodeAttribute::eBoundary:
                
                break;
            case FbxNodeAttribute::eNurbsSurface:
                printf("nurbs surface obj\n");
                break;
            case FbxNodeAttribute::eShape:
                printf("shaoe obj\n");
                break;
            case FbxNodeAttribute::eLODGroup:
                printf("LOG group obj\n");
                break;
            case FbxNodeAttribute::eSubDiv:
                printf("sib div obj\n");
                break;
            case FbxNodeAttribute::eCachedEffect:
                printf("cached effect obj\n");
                break;
            case FbxNodeAttribute::eLine:
                printf("line obj\n");
                break;
            default:
                break;
        }
    }else{
        printf("------\n");
        m_position = Point3D(translation[0], translation[1], translation[2]);
        m_scale = Point3D(scaling[0], scaling[1], scaling[2]);
        m_locEuler = Point3D(rotation[0], rotation[1], rotation[2]);
        this->setName(nodeName);
    }
    
    for (int i=0; i<node->GetChildCount(); ++i) {
        this->processNodeInfo(node->GetChild(i));
    }
}

void PEModelFBX::ProcessMeshInfo(FbxNode *node)
{
    PEModelFBX *model = PEModelFBX::createWithFbxNode(node);
    this->addChild(model, model->getName());
}

void PEModelFBX::displayControlPoints(FbxMesh *mesh)
{
    int lControlPoinsCount = mesh->GetControlPointsCount();
    FbxVector4 *lControlPoints = mesh->GetControlPoints();
    for (int i=0; i<lControlPoinsCount; ++i) {
        printf("Controll Point Coordinates[%d]: %f, %f, %f\n", i, lControlPoints[i][0],
               lControlPoints[i][1], lControlPoints[i][2]);
        for(int j=0; j<mesh->GetElementNormalCount(); ++j){
            FbxGeometryElementNormal *leNormals = mesh->GetElementNormal(j);
            if(leNormals->GetMappingMode() == FbxGeometryElement::eByControlPoint){
                char header[100];
                FBXSDK_snprintf(header, 100, "    Normal Vector:");
                if(leNormals->GetReferenceMode() == FbxGeometryElement::eDirect){
                    printf("%s (%f, %f, %f)\n", header, leNormals->GetDirectArray().GetAt(j)[0],
                           leNormals->GetDirectArray().GetAt(j)[1], leNormals->GetDirectArray().GetAt(j)[2]);
                }
            }
        }
    }
}

void PEModelFBX::displayPolygons(FbxMesh *mesh)
{
    int j, polygonCount = mesh->GetPolygonCount();
    FbxVector4 *lControlPoints = mesh->GetControlPoints();
    char header[100];
    
    int vertexId = 0;
    for(int i=0; i<polygonCount; ++i){
        printf("Polygon %d\n", i);
        for(int l=0; l<mesh->GetElementPolygonGroupCount(); ++l){
            FbxGeometryElementPolygonGroup *lePoglgrp = mesh->GetElementPolygonGroup(l);
            switch (lePoglgrp->GetMappingMode()) {
                case FbxGeometryElement::eByPolygon:
                    if(lePoglgrp->GetReferenceMode() == FbxGeometryElement::eIndex){
                        FBXSDK_snprintf(header, 100, "  Assigned to group");
                        int polygonGroupId = lePoglgrp->GetIndexArray().GetAt(i);
                        printf("%s %d\n", header, polygonGroupId);
                    }
                    break;
                default:
                    printf("unsupported group assignment\n");
                    break;
            }
        }
        int lPolygonSize = mesh->GetPolygonSize(i);
        for(int j=0; j<lPolygonSize; ++j){
            int lControlPointIndex = mesh->GetPolygonVertex(i, j);
            printf("[%d]:(%f, %f, %f)\n", lControlPointIndex, lControlPoints[lControlPointIndex][0],
                   lControlPoints[lControlPointIndex][1], lControlPoints[lControlPointIndex][2]);
            
            
        }
    }
    
    
}
