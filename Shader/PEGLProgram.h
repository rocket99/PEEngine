//
//  PEGLProgram.h
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef __Engine__PEGLProgram__
#define __Engine__PEGLProgram__

#include <iostream>
#include "../PEPrefix.h"

class PEGLProgram
{
public:
    PEGLProgram(const char *vert, const char *frag);
    ~PEGLProgram();
    
    GLuint getProgram();
private:
    GLuint m_program;
    
    GLint compileShader(GLenum type, const char *src);
    void linkProgram(GLint vert, GLint frag);
};

#endif /* defined(__Engine__PEGLProgram__) */
