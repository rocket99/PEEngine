//
//  PEFbxModel.cpp
//  Engine
//
//  Created by rocket99 on 14-9-18.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEFbxModel.h"

PEModelFBX::PEModelFBX():m_polygonData(NULL),
m_polygonNum(0), m_triangleNum(0), m_vertData(NULL)
{}

PEModelFBX::~PEModelFBX()
{
    delete [] m_vertData;
    deletePolygons();
}
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
    lImporter->Destroy();
    
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

    this->setPolygonData(mesh);
    this->setDrawTriangleData();
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
        this->setRotate(m_locEuler, PENode::Euler_XYZ);
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


void PEModelFBX::setPolygonData(FbxMesh *mesh)
{
    int vertexId = 0;
    FbxVector4 *ctrlPoints = mesh->GetControlPoints();
    m_polygonNum = mesh->GetPolygonCount();
    m_polygonData = new Polygon[mesh->GetPolygonCount()];
    for(int i=0; i<mesh->GetPolygonCount(); ++i){
        int polySize = mesh->GetPolygonSize(i);
        m_polygonData[i].pointNum = polySize;
        m_polygonData[i].coodinates = new P3D [polySize];
        m_polygonData[i].normals = new P3D [polySize];
        m_polygonData[i].uvCoords = new P2D [polySize];
        for(int j=0; j<polySize; ++j){
            int index = mesh->GetPolygonVertex(i, j);
            m_polygonData[i].coodinates[j] = Point3D(ctrlPoints[index][0],
                                                     ctrlPoints[index][1],
                                                     ctrlPoints[index][2]);
            //法线
            for (int l=0; l<mesh->GetElementNormalCount(); ++l) {
                FbxGeometryElementNormal *leNormal = mesh->GetElementNormal(l);
                if (leNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
                    switch (leNormal->GetReferenceMode()) {
                        case FbxGeometryElement::eDirect:
                        {
                            FbxDouble3 tmpNormal = leNormal->GetDirectArray().GetAt(vertexId);
                            m_polygonData[i].normals[j] = Point3D(tmpNormal[0], tmpNormal[1], tmpNormal[2]);
                        }
                            break;
                        case FbxGeometryElement::eIndexToDirect:
                        {
                            int id = leNormal->GetIndexArray().GetAt(vertexId);
                            FbxDouble3 tmpNormal = leNormal->GetDirectArray().GetAt(id);
                            m_polygonData[i].normals[j] = Point3D(tmpNormal[0], tmpNormal[1], tmpNormal[2]);
                        }
                            break;
                        default:
                            break;
                    }
                }
            }
            //纹理坐标
            for(int l=0; l<mesh->GetElementUVCount(); ++l){
                FbxGeometryElementUV *leUV = mesh->GetElementUV(l);
                switch (leUV->GetMappingMode()) {
                    case FbxGeometryElement::eByControlPoint:
                    {
                        switch (leUV->GetReferenceMode()) {
                            case FbxGeometryElement::eDirect:
                            {
                                FbxDouble2 tmpUV = leUV->GetDirectArray().GetAt(index);
                                m_polygonData[i].uvCoords[j] = Point2D(tmpUV[0], tmpUV[1]);
                            }
                                break;
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                int id = leUV->GetIndexArray().GetAt(index);
                                FbxDouble2 tmpUV = leUV->GetDirectArray().GetAt(id);
                                m_polygonData[i].uvCoords[j] = Point2D(tmpUV[0], tmpUV[1]);
                            }
                                break;
                            default:
                                break;
                        }
                    }
                        break;
                    case FbxGeometryElement::eByPolygonVertex:
                    {
                        int texUVIndex = mesh->GetTextureUVIndex(i, j);
                        switch (leUV->GetReferenceMode()) {
                            case FbxGeometryElement::eDirect:
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                FbxDouble2 tmpUV = leUV->GetDirectArray().GetAt(texUVIndex);
                                m_polygonData[i].uvCoords[j] = Point2D(tmpUV[0], tmpUV[1]);
                            }
                                break;
                            default:
                                break;
                        }
                    }
                        break;
                    case FbxGeometryElement::eByPolygon:
                    case FbxGeometryElement::eAllSame:
                    case FbxGeometryElement::eNone:
                        break;
                    default:
                        break;
                }
            }
//            printf("[%d]:coord(%.3f, %.3f, %.3f), normal(%.3f, %.3f, %.3f), uv(%.3f, %.3f)\n", j,
//                   m_polygonData[i].coodinates[j].x, m_polygonData[i].coodinates[j].y, m_polygonData[i].coodinates[j].z,
//                   m_polygonData[i].normals[j].x, m_polygonData[i].normals[j].y, m_polygonData[i].normals[j].z,
//                   m_polygonData[i].uvCoords[j].x, m_polygonData[i].uvCoords[j].y);
        }
        ++ vertexId;
    }
}

void PEModelFBX::deletePolygons()
{
    for(int i=0; i<m_polygonNum; ++i){
        delete [] m_polygonData[i].coodinates;
        delete [] m_polygonData[i].normals;
        delete [] m_polygonData[i].uvCoords;
    }
    delete [] m_polygonData;
    m_polygonNum = 0;
    m_polygonData = NULL;
}

void PEModelFBX::setDrawTriangleData()
{
    m_triangleNum = 0;
    for(int i=0; i<m_polygonNum; ++i){
        m_triangleNum += m_polygonData[i].pointNum-2;
    }
    int index = 0;
    m_vertData = new GLfloat [m_triangleNum *(3*3+3*3+3*2)];
    for(int i=0; i<m_polygonNum; ++i){
        for(int j=1; j<m_polygonData[i].pointNum-1; ++j){
            m_vertData[index ++] = m_polygonData[i].coodinates[0].x;
            m_vertData[index ++] = m_polygonData[i].coodinates[0].y;
            m_vertData[index ++] = m_polygonData[i].coodinates[0].z;
            m_vertData[index ++] = m_polygonData[i].normals[0].x;
            m_vertData[index ++] = m_polygonData[i].normals[0].y;
            m_vertData[index ++] = m_polygonData[i].normals[0].z;
            m_vertData[index ++] = m_polygonData[i].uvCoords[0].x;
            m_vertData[index ++] = m_polygonData[i].uvCoords[0].y;
            
            m_vertData[index ++] = m_polygonData[i].coodinates[j].x;
            m_vertData[index ++] = m_polygonData[i].coodinates[j].y;
            m_vertData[index ++] = m_polygonData[i].coodinates[j].z;
            m_vertData[index ++] = m_polygonData[i].normals[j].x;
            m_vertData[index ++] = m_polygonData[i].normals[j].y;
            m_vertData[index ++] = m_polygonData[i].normals[j].z;
            m_vertData[index ++] = m_polygonData[i].uvCoords[j].x;
            m_vertData[index ++] = m_polygonData[i].uvCoords[j].y;
            
            m_vertData[index ++] = m_polygonData[i].coodinates[j+1].x;
            m_vertData[index ++] = m_polygonData[i].coodinates[j+1].y;
            m_vertData[index ++] = m_polygonData[i].coodinates[j+1].z;
            m_vertData[index ++] = m_polygonData[i].normals[j+1].x;
            m_vertData[index ++] = m_polygonData[i].normals[j+1].y;
            m_vertData[index ++] = m_polygonData[i].normals[j+1].z;
            m_vertData[index ++] = m_polygonData[i].uvCoords[j+1].x;
            m_vertData[index ++] = m_polygonData[i].uvCoords[j+1].y;
        }
    }
}

void PEModelFBX::draw()
{
    if(!m_isVisible){
        return;
    }
    PENode::draw();
    if (GL_FALSE == glIsProgram(m_program1)) {
        return;
    }
    if (m_vertData != NULL) {
        m_program = m_program1;
        this->setModelViewProjectUniform();
        this->setLightProjectViewUniform();
        this->setDepthTexUnifrom();
        this->drawFunc();
    }
}

void PEModelFBX::drawFBO()
{
    if(!m_isVisible){
        return;
    }
    PENode::drawFBO();
    
    if(GL_FALSE == glIsProgram(m_program0)){
        return;
    }
    if(m_vertData != NULL){
        m_program = m_program0;
        this->setLightProjectViewUniform(UNIFORM_MODELPROJECT);
        this->drawFunc();
    }
}

void PEModelFBX::drawFunc()
{
    glUseProgram(m_program);
    
    this->setSpaceUniform();
    this->setWorldMatUniform();
    this->setColorUniform();
    this->setTextureUniform();
    this->setCameraPosUniform();
    
    glEnableVertexAttribArray(ATTRIB_POINT_LOC);
    glVertexAttribPointer(ATTRIB_POINT_LOC, 3, GL_FLOAT, GL_FALSE, 8, &m_vertData[0]);
    glEnableVertexAttribArray(ATTRIB_NORMAL_LOC);
    glVertexAttribPointer(ATTRIB_NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 8, &m_vertData[3]);
    glEnableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glVertexAttribPointer(ATTRIB_TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 8, &m_vertData[6]);
    glDrawArrays(0, GL_TRIANGLES, m_triangleNum*3);
    glDisableVertexAttribArray(ATTRIB_POINT_LOC);
    glDisableVertexAttribArray(ATTRIB_TEXCOORD_LOC);
    glDisableVertexAttribArray(ATTRIB_NORMAL_LOC);
}


