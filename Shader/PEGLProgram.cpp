//
//  PEGLProgram.cpp
//  Engine
//
//  Created by rocket99 on 14-8-21.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#include "PEGLProgram.h"

PEGLProgram::PEGLProgram():m_program(0)
{}

PEGLProgram::~PEGLProgram()
{
	if(GL_FALSE == glIsProgram(m_program)){
		glDeleteProgram(m_program);
	}
}

PEGLProgram *PEGLProgram::createWithVertFragSrc(const char *vert, const char *frag)
{
//	printf("vertex shader: %s\n", vert);
//	printf("frag shader:%s\n", frag);

	PEGLProgram *program = new PEGLProgram();
	if(program->initWithVertFragSrc(vert, frag)){
		return program;
	}
	delete program;
	return NULL;
}

bool PEGLProgram::initWithVertFragSrc(const char *vert, const char *frag)
{
    GLint vShader = compileShader(GL_VERTEX_SHADER, vert);
	if(GL_FALSE == glIsShader(vShader)){
		return false;
	}
	GLint fShader = compileShader(GL_FRAGMENT_SHADER, frag);
    if(GL_FALSE == glIsShader(fShader)){
		return false;
	}
	linkProgram(vShader, fShader);

	return true;
}

GLint PEGLProgram::compileShader(GLenum type, const char *src)
{
    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint status = GL_FALSE;
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
    GLint linked = GL_FALSE;
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

GLuint PEGLProgram::getProgram()
{
    return m_program;
}
