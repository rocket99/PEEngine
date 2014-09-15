
//PETexture.cpp
//

#include "PETexture.h"
#include <png.h>
PETexture::PETexture()
{
	m_Id = 0;
}

PETexture::~PETexture()
{

}

PETexture *PETexture::create(const char *fileName, PicType type)
{
	PETexture *texture = new PETexture();
	if(texture->initWithPic(fileName, type)){
		return texture;
	}
	delete texture;
	return NULL;
}

bool PETexture::initWithPic(const char *fileName, PicType type)
{
	switch(type){
		case PNG_PIC:
			return this->readPNGFile(fileName);
			break;
		case JPG_PIC:
			return this->readJPGFile(fileName);
			break;
		default:
			return false;
			break;
	}
	return true;
}

GLuint PETexture::Texture()
{
	return m_Id;
}

int PETexture::Width()
{
	return m_width;
}

int PETexture::Height()
{
	return m_height;
}

bool PETexture::readPNGFile(const char *fileName)
{
	FILE *fp = fopen(fileName, "rb");
	if(NULL == fp){
		return false;
	}
	
	return true;
}

bool PETexture::readJPGFile(const char *fileName)
{
	/*
	FILE *fp = fopen(fileName, "rb");
	if(NULL == fp){
		return false;
	}
	char header[10];
	fread(header, 1, 8, fp);
	header[8] - '\0';
	bool is_png = !png_sig_cmp(header, 0, 8);
	if(!is_png){
		return false;
	}
*/
	return true;
}


