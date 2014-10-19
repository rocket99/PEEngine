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
	static PEGLProgram *createWithVertFragSrc(const char *vert, const char *frag);
	bool initWithVertFragSrc(const char *vert, const char *frag);
#ifdef GL_LINUX
	static PEGLProgram *create(const char *vert, const char * geometry, const char *frag);
	bool init(const char *vert, const char *geometry, const char *frag);

	static PEGLProgram *create(const char *vert, const char *tessCtrl, const char *tessEva, 
								const char *geometry const char *frag);
	bool init(const char *vert, const char *tessCtrl, const char *tessEva,
				const char *geometry, const char *frag);
#endif
    PEGLProgram();
    ~PEGLProgram();
    
    GLuint getProgram();
private:
    GLuint m_program;
    
    GLint compileShader(GLenum type, const char *src);
    void linkProgram(GLint vert, GLint frag);
#ifdef GL_LINUX
	void linkProgram(GLint vShader, GLint gShader, GLint fShader);
	void linkProgram(GLint vShader, GLint tcShader, GLint tvShader, GLint gShader, GLint fShader);
#endif
};

#endif /* defined(__Engine__PEGLProgram__) */
