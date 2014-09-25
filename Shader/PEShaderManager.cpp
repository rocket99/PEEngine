//
//  PEShaderManager.cpp
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEShaderManager.h"

static PEShaderManager *instance = NULL;

PEShaderManager::PEShaderManager()
{
    
}

PEShaderManager::~PEShaderManager()
{
    map<string, PEGLProgram *>::iterator it = m_allProgram.begin();
    while (it != m_allProgram.end()) {
        delete it->second;
        ++ it;
    }
}

PEShaderManager *PEShaderManager::Instance()
{
    if(instance == NULL){
        instance = new PEShaderManager;
    }
    return instance;
}

void PEShaderManager::purge()
{
    delete instance;
    instance = NULL;
}

void PEShaderManager::setProgramForKey(PEGLProgram *prog, const char *key)
{
    m_allProgram[key] = prog;
}

GLuint PEShaderManager::getProgramForKey(const char *key)
{
    if (m_allProgram[key] == NULL) {
        return GL_FALSE;
    }
    return m_allProgram[key]->getProgram();
}
