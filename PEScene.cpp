//
// PEScene.cpp
//

#include "PEEngine.h"

PEScene::PEScene(){
	m_width = 0;
	m_height = 0;
	m_pWindow = NULL;
}

PEScene::~PEScene(){
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();	
}

PEScene * PEScene::createWithSize(string name, int width, int height)
{
	PEScene *scene = new PEScene();
	if(scene->initWithSize(name, width, height)){
		return scene;
	}
	delete scene;
	return NULL;
}

bool PEScene::initWithSize(string name, int width, int height)
{
	if(!PENode::init()){
		return false;
	}
	m_name = name;
	m_width = width;
	m_height = height;
	int ret = glfwInit();
	if(ret == 0){
		return false;
	}
	m_pWindow = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
	if(NULL == m_pWindow){
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_pWindow);	
	
	this->setFrameBuffer();
	this->setGLPrograms();
	this->setWorldMat();
	glEnable(GL_DEPTH_TEST);

	PEKeyboardManager::getInstance()->setEventView(m_pWindow);
	m_event = new PEKeyboardEvent(GLFW_KEY_SPACE);
	m_event->setSceneIn(m_pWindow);
	m_event->setPressEndFunction(std::bind(&PEScene::saveViewToPicture, this));
	PEKeyboardManager::getInstance()->addKeyboardEvent(m_event);
	return true;
}

void PEScene::start()
{
	while(!glfwWindowShouldClose(m_pWindow)&& glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS){
		this->drawFBO();
		this->draw();
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
		PEKeyboardManager::getInstance()->checkAllEvents();
	}
}

void PEScene::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_MULTISAMPLE);
//	glSampleCoverage(0.05, GL_TRUE);
//	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB8, m_width, m_height);
//	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, m_width, m_height);

	for(int i=0; i<m_children.size(); ++i){
		m_children[i]->draw();
	}
}

void PEScene::drawFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.75, 0.75, 0.75, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for(int i=0; i<m_children.size(); ++i){
		m_children[i]->drawFBO();
	}
}

int PEScene::Width()
{
	return m_width;
}

int PEScene::Height()
{
	return m_height;
}

void PEScene::setFrameBuffer()
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
//color
	glGenTextures(1, &m_colorTex);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_colorTex);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_RGBA8, m_width, m_height, GL_TRUE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colorTex, 0);
//depth
	GLfloat border[] = {1.0f, 0.0f, 0.0f, 0.0f};
	glGenTextures(1, &m_depthTex);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_depthTex);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BORDER_COLOR, border);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_DEPTH_COMPONENT, m_width, m_height, GL_TRUE);	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_depthTex, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	PETextureManager::Instance()->DepthTex() = m_depthTex;
	PETextureManager::Instance()->ColorTex() = m_colorTex;
}

void PEScene::setGLPrograms(){
	std::string vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/vert_tex.vsh");
	std::string frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/vert_tex.fsh");
	PEGLProgram *program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "vert_tex");	
	
	vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/light.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/light.fsh");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "light");	
	
	vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/shadow.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/shadow.fsh");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "shadow");	
	
	vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/normal.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/normal.fsh");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "normal");	

	vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/vert_color.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/vert_color.fsh");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "vert_color");

	vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/normal_map.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/normal_map.fsh");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "normal_map");
	
	vert = PEShaderReader::readShaderSrc("./Shader/GL4.0/Julia.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/GL4.0/Julia.fsh");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "julia");
}

void PEScene::saveViewToPicture(){
	GLubyte *data = new GLubyte[m_width*m_height*4];
	memset(data, 0, sizeof(char)*4*m_width*m_height);
	glReadPixels(0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *tow_pointers;

	FILE *fp = fopen("a.png", "wb");
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, fp);
	if(setjmp(png_jmpbuf(png_ptr))){
		PELog("write png file error during write header");
		return;
	}
	
	png_set_IHDR(png_ptr, info_ptr, m_width, m_height, 8, PNG_COLOR_TYPE_RGB_ALPHA, 
				PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	setjmp(png_jmpbuf(png_ptr));

	int pos = 0;
	png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*m_height);
	for(int i=0; i<m_height; ++i){
		row_pointers[i] = (png_bytep)malloc(sizeof(unsigned char)*m_width*4);
		for(int j=0; j<4*m_width; j+=4){
			row_pointers[i][j+0] = data[(m_height-1-i)*4*m_width+j];
			row_pointers[i][j+1] = data[(m_height-1-i)*4*m_width+j+1];
			row_pointers[i][j+2] = data[(m_height-1-i)*4*m_width+j+2];
			row_pointers[i][j+3] = data[(m_height-1-i)*4*m_width+j+3];
		}
	}
	png_write_image(png_ptr, row_pointers);
	if(setjmp(png_jmpbuf(png_ptr))){
		printf("write png file error during end of write!\n");
		return;
	}
	for(int j=0; j<m_height;++j){
		free(row_pointers[j]);
	}
	free(row_pointers);
	fclose(fp);
	delete [] data; 
}

void PEScene::displayHardwareInfo()
{
	int num;
	glGetIntegerv(GL_SAMPLE_BUFFERS, &num);
	PELog("sample num %d", num);
	glGetIntegerv(GL_SAMPLES, &num);
	PELog("samples %d", num);
}



