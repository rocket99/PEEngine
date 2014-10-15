//
// PEScene.cpp
//

#include "PEScene.h"

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
	glEnable(GL_DEPTH_TEST);
	m_scene = TestScene::create(GLOBAL_WORLD_SIZE);
	
	return true;
}

void PEScene::start()
{
	while(!glfwWindowShouldClose(m_pWindow)&& glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS){
		this->drawFBO();
		this->draw();
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}

void PEScene::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.4, 0.4, 0.4, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_scene->draw();
}

void PEScene::drawFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
	glClearColor(0.40, 0.4, 0.4, 0.5);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	m_scene->drawFBO();
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

	glGenTextures(1, &m_colorTex);
	glBindTexture(GL_TEXTURE_2D, m_colorTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &m_depthTex);
	glBindTexture(GL_TEXTURE_2D, m_depthTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_width, m_height, 0, 
				GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	PETextureManager::Instance()->DepthTex() = m_depthTex;
	PETextureManager::Instance()->ColorTex() = m_colorTex;
}

void PEScene::setGLPrograms()
{
	std::string vert = PEShaderReader::readShaderSrc("./Shader/vertColor_Linux.vsh");
	std::string frag = PEShaderReader::readShaderSrc("./Shader/vertColor_Linux.fsh");
	PEGLProgram *program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "vertColor");
	vert = PEShaderReader::readShaderSrc("./Shader/light_Linux.vsh");
	frag = PEShaderReader::readShaderSrc("./Shader/light_Linux.fsh");
	PELog("link light GL program");
	program = PEGLProgram::createWithVertFragSrc(vert.c_str(), frag.c_str());
	PEShaderManager::Instance()->setProgramForKey(program, "light");
}

