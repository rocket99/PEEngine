
//PETexture.cpp
//

#include "PETexture.h"

#define PNG_BYTES_TO_CHECK 4
PETexture::PETexture()
{
	m_Id = 0;
}

PETexture::~PETexture()
{
	if(GL_TRUE == glIsTexture(m_Id)){
		glDeleteTextures(1, &m_Id);
	}
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
	temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
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
	GLubyte *data = new GLubyte [m_width*m_height*4];
	w = m_width; h = m_height;
	long pos = 0;
	switch(color_type){
		case PNG_COLOR_TYPE_RGB_ALPHA:
			for(y=0; y<h;++y){
				for(x=0; x<4*w; x+=4){
					data[pos++] = row_pointers[y][x+0];
					data[pos++] = row_pointers[y][x+1];
					data[pos++] = row_pointers[y][x+2];
					data[pos++] = row_pointers[y][x+3];
				}
			}
			break;
		case PNG_COLOR_TYPE_RGB:
			PELog("png without alpha");
			for(y=0; y<m_height; ++y){
				for(x=0; x<w; ++x){
					data[pos++] = row_pointers[y][3*x+0];
					data[pos++] = row_pointers[y][3*x+1];
					data[pos++] = row_pointers[y][3*x+2];
					data[pos++] = 255;
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
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, true);
	m_width = cinfo.image_width;
	m_height = cinfo.image_height;
	
	GLubyte *data = new GLubyte[m_width*m_height*cinfo.num_components];
	jpeg_start_decompress(&cinfo);
	JSAMPROW row_pointer[1];
	while(cinfo.output_scanline < cinfo.output_height){
		row_pointer[0] = &data[cinfo.output_scanline*cinfo.image_width*cinfo.num_components];
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(fp);
	GLubyte *data0 = new GLubyte[m_width*m_height*4];
	for(int i=0; i<m_height; ++i){
		for(int j=0; j<m_width; ++j){
			data0[4*(i*m_width+j)+0] = data[3*(i*m_width+j)+0];
			data0[4*(i*m_width+j)+1] = data[3*(i*m_width+j)+1];
			data0[4*(i*m_width+j)+2] = data[3*(i*m_width+j)+2];
			data0[4*(i*m_width+j)+3] = 255;
		}
	}
	delete [] data;
	this->createTexture(data0);
	delete [] data0;
	return true;
}

void PETexture::createTexture(GLubyte *data)
{
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_width, (GLsizei)m_height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}


