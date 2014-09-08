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

class PETexture
{
public:
	enum {
		PNG_PIC,
		JPG_PIC,
	}PicType;
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

	void readPNGFile(const char *fileName);
	void readJPGFile(const char *fileName);
};


#endif
