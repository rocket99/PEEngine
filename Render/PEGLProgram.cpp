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
		glDeleteShader(vShader);
		return false;
	}
	linkProgram(vShader, fShader);

	return true;
}

#ifdef GL_LINUX
PEGLProgram *PEGLProgram::create(const char *vert, const char *geometry, const char *frag)
{
	PEGLProgram *program = new PEGLProgram();
	if(program->init(vert, geometry, frag)){
		return program;
	}
	delete program;
	return NULL;
}

bool PEGLProgram::init(const char *vert, const char *geometry, const char *frag)
{
	GLint vShader = compileShader(GL_VERTEX_SHADER, vert);
	if(GL_FALSE == glIsShader(vShader)){
		return false;
	}
	GLint gShader = compileShader(GL_GEOMETRY_SHADER, geometry);
	if(GL_FALSE == glIsShader(gShader)){
		glDeleteShader(gShader);
		return false;
	}
	GLint fShader = compileShader(GL_FRAGMENT_SHADER, frag);
	if(GL_FALSE == glIsShader(fShader)){
		glDeleteShader(vShader);
		glDeleteShader(gShader);
		return false;
	}
	this->linkProgram(vShader, gShader, fShader);
	return true;
}

PEGLProgram *PEGLProgram::create(const char *vert, const char *tessCtrl, const char *tessEva,
									const char *geometry, const char *frag){
	PEGLProgram *program = new PEGLProgram();
	if(program->init(vert, tessCtrl, tessEva, geometry, frag)){
		return program;
	}
	delete program;
	return NULL;
}

bool PEGLProgram::init(const char *vert, const char *tessCtrl, const char *tessEva, 
						const char *geometry, const char *frag){

	GLint vShader = compileShader(GL_VERTEX_SHADER, vert);
	if(GL_FALSE == glIsShader(vShader)){
		return false;
	}
	GLint gShader = compileShader(GL_GEOMETRY_SHADER, geometry);
	if(GL_FALSE == glIsShader(gShader)){
		glDeleteShader(gShader);
		return false;
	}
	GLint tcShader = compileShader(GL_TESS_CONTROL_SHADER, tessCtrl);
	if(GL_FALSE == glIsShader(tcShader)){
		glDeleteShader(vShader);
		glDeleteShader(gShader);
		return false;
	}
	GLint tvShader = compileShader(GL_TESS_EVALUATION_SHADER, tessEva);
	if(GL_FALSE == glIsShader(tvShader)){
		glDeleteShader(vShader);
		glDeleteShader(gShader);
		glDeleteShader(tcShader);
		return false;
	}
	GLint fShader = compileShader(GL_FRAGMENT_SHADER, frag);
	if(GL_FALSE == glIsShader(fShader)){
		glDeleteShader(vShader);
		glDeleteShader(gShader);
		glDeleteShader(tcShader);
		glDeleteShader(tvShader);
		return false;
	}

	this->linkProgram(vShader, tcShader, tvShader, gShader, fShader);
	return true;
}
#endif

GLint PEGLProgram::compileShader(GLenum type, const char *src)
{
	if(src == NULL){
		return GL_FALSE;
	}
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
#ifdef GL_LINUX
void PEGLProgram::linkProgram(GLint vShader, GLint gShader, GLint fShader)
{
    if(vShader == GL_FALSE || gShader == GL_FALSE || fShader == GL_FALSE){
        return;
    }
    m_program= glCreateProgram();
    glAttachShader(m_program, vShader);
    glAttachShader(m_program, gShader);
    glAttachShader(m_program, fShader);
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
        glDetachShader(m_program, vShader);
        glDetachShader(m_program, gShader);
        glDetachShader(m_program, fShader);
        glDeleteShader(vShader);
        glDeleteShader(gShader);
        glDeleteShader(fShader);
        glDeleteProgram(m_program);
        m_program = GL_FALSE;
        return;
    }
    glDetachShader(m_program, vShader);
    glDetachShader(m_program, gShader);
    glDetachShader(m_program, fShader);
    glDeleteShader(vShader);
    glDeleteShader(gShader);
    glDeleteShader(fShader);
}

void PEGLProgram::linkProgram(GLint vShader, GLint tcShader, GLint tvShader, GLint gShader, GLint fShader)
{
    if(vShader==GL_FALSE || tcShader==GL_FALSE || tvShader==GL_FALSE || gShader==GL_FALSE || fShader==GL_FALSE){
        return;
    }
    m_program= glCreateProgram();
    glAttachShader(m_program, vShader);
    glAttachShader(m_program, tcShader);
    glAttachShader(m_program, tvShader);
    glAttachShader(m_program, gShader);
    glAttachShader(m_program, fShader);
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
        glDetachShader(m_program, vShader);
        glDetachShader(m_program, tcShader);
        glDetachShader(m_program, tvShader);
        glDetachShader(m_program, gShader);
        glDetachShader(m_program, fShader);
        glDeleteShader(vShader);
        glDeleteShader(tcShader);
        glDeleteShader(tvShader);
        glDeleteShader(gShader);
        glDeleteShader(fShader);
        glDeleteProgram(m_program);
        m_program = GL_FALSE;
        return;
    }
    glDetachShader(m_program, vShader);
    glDetachShader(m_program, tcShader);
    glDetachShader(m_program, tvShader);
    glDetachShader(m_program, gShader);
    glDetachShader(m_program, fShader);
    glDeleteShader(vShader);
    glDeleteShader(tcShader);
    glDeleteShader(tvShader);
    glDeleteShader(gShader);
    glDeleteShader(fShader);
}
#endif

GLuint PEGLProgram::getProgram()
{
    return m_program;
}
