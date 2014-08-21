//
//  PEGLProgram.cpp
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEGLProgram.h"

PEGLProgram::PEGLProgram(const char *vert, const char *frag)
{
    
}

PEGLProgram::~PEGLProgram()
{
    glDeleteProgram(m_program);
}

GLint PEGLProgram::compileShader(GLenum type, const char *src)
{
    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        GLint size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
        char *log = (char *)malloc(sizeof(char)*size);
        glGetShaderInfoLog(shader, size, NULL, log);
        printf("%s", log);
        free(log);
        glDeleteShader(shader);
        shader = GL_FALSE;
    }
    return shader;
}

void PEGLProgram::linkProgram(GLint vert, GLint frag)
{
    if(vert == GL_FALSE || frag == GL_FALSE){
        return;
    }
    m_program= glCreateProgram();
    glAttachShader(m_program, vert);
    glAttachShader(m_program, frag);
    glLinkProgram(m_program);
    GLint linked;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
    if(linked == GL_FALSE){
        GLint len;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &len);
        char *log = (char *)malloc(sizeof(char)*len);
        glGetProgramInfoLog(m_program, len, NULL, log);
        printf("%s\n", log);
        free(log);
        glDetachShader(m_program, vert);
        glDetachShader(m_program, frag);
        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteProgram(m_program);
        m_program = GL_FALSE;
        return;
    }
    glDetachShader(m_program, vert);
    glDetachShader(m_program, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
}