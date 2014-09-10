//
//  PETexture.h
//  Engine
//
//  Created by rocket99 on 14-8-27.
//  Copyright (c) 2014年 rocket99. All rights reserved.
//

#ifndef Engine_PETexture_h
#define Engine_PETexture_h

#include "PEPrefix.h"

static GLuint DepthTex;
static GLuint ColorTex;

class PETexture
{
public:
	enum PicType{
		PNG_PIC,
		JPG_PIC,
	};
    
    PETexture();
    ~PETexture();
    
    static PETexture *create(const char *fileName, PicType type);
    bool initWithPic(const char *fileName, PicType type);
    GLuint Texture();
    int Width();
    int Height();
    
   
private:
    
    int m_width, m_height;
    GLuint m_Id;

	bool readPNGFile(const char *fileName);
	bool readJPGFile(const char *fileName);
};


#endif
