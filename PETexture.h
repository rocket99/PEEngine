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
	enum PicType{
		PNG_PIC,
		JPG_PIC,
        CUBE_PIC,
	};
    
    PETexture();
    ~PETexture();
    
    static PETexture *create(const char *fileName, PicType type);
    bool initWithPic(const char *fileName, PicType type);

	static PETexture *createWithFont(const std::string &content, const std::string &font, float size);
	bool initWithFont(const std::string &constent, const std::string &font, float size);
    GLuint Texture();
    int Width();
    int Height();
    
    static PETexture *createCubeTex(const char *fileName);
    bool initWithCubeMap(const char *fileName);
private:
    
    int m_width, m_height;
    GLuint m_Id;

	bool readPNGFile(const char *fileName);
	bool readJPGFile(const char *fileName);
    void createTexture(GLubyte *data);

};


#endif
