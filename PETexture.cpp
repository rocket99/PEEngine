
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
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep * row_pointers;
	char buf[PNG_BYTES_TO_CHECK];
	int w, h, x, y, temp, color_type;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	info_ptr = png_create_info_struct(png_ptr);
	setjmp(png_jmpbuf(png_ptr));
	temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
	if(temp < PNG_BYTES_TO_CHECK){
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}
	temp = png_sig_cmp((png_bytep)buf, (png_size)0, PNG_BYTES_TO_CHECK);
	if(temp != 0){
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}
	rewind(fp);
	png_init_io(png_ptr, fp);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
	color_type = png_get_color_type(png_ptr, info_ptr);

	m_width = png_get_image_width(png_ptr, info_ptr);
	m_height = png_get_image_height(png_ptr, info_ptr);
	row_pointers = png_get_rows(png_ptr, info_ptr);
	GLbyte *data = new GLbyte [m_width*m_height*4];;
	switch(color_type){
		case PNG_COLOR_TYPE_RGB_ALPHA:
			for(y=0; y<h;++y){
				for(x=0; x<w; ++x){
					data[(y*w+x)*4+0] = row_pointer[y][x+0];
					data[(y*w+x)*4+1] = row_pointer[y][x+1];
					data[(y*w+x)*4+2] = row_pointer[y][x+2];
					data[(y*w+x)*4+3] = row_pointer[y][x+3];
				}
			}
			break;
		case PNG_COLOR_TYPE_RGB:
			for(y=0; y<h; ++y){
				for(x=0; x<w; ++x){
					data[(y*w+x)*4+0] = row_pointer[y][x+0];
					data[(y*w+x)*4+1] = row_pointer[y][x+1];
					data[(y*w+x)*4+2] = row_pointer[y][x+2];
					data[(y*w+x)*4+3] = 255;
				}
			}
			break;
		default:
			fclose(fp);
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			return false;
	};
	fclose(fp);
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	this->createTexture(data);
	delete [] data;
	return true;
}

bool PETexture::readJPGFile(const char *fileName)
{
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

	return true;
}

void PETexture::createTexture(GLbyte *data)
{
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_width, (GLsizei)m_height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}


