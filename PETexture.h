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
    PETexture();
    ~PETexture();
    
    static PETexture *create(const char *fileName);
    bool initWithPic(const char *fileName);
    GLuint getTexture();
    int getWidth();
    int getHeight();
private:
    int m_width, m_height;
    GLuint m_Id;
};


#endif
