//
//  PETextureManager.cpp
//  Engine
//
//  Created by rocket99 on 14-9-10.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PETextureManager.h"

static PETextureManager *instance = NULL;
PETextureManager *PETextureManager::Instance()
{
    if (instance == NULL) {
        instance = new PETextureManager;
    }
    return instance;
}

void PETextureManager::purge()
{
    if(instance != NULL){
        delete instance;
    }
    instance = NULL;
}

GLuint &PETextureManager::ColorTex()
{
    return m_colorTex;
}

GLuint &PETextureManager::DepthTex()
{
    return m_depthTex;
}

