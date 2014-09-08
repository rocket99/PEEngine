//
//  PEShaderManager.h
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEShaderManager__
#define __Engine__PEShaderManager__

#include <iostream>
#include "../PEPrefix.h"
#include "PEGLProgram.h"

class PEShaderManager
{
public:
    PEShaderManager();
    ~PEShaderManager();
    static PEShaderManager *Instance();
    static void purge();
    
    void setProgramForKey(PEGLProgram *prog, const char *key);
    GLuint getProgramForKey(const char *key);
private:
    map<string, PEGLProgram*> m_allProgram;
};
#endif /* defined(__Engine__PEShaderManager__) */
