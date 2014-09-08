//
// PEScene.cpp
//

#include "PEScene.h"

PEScene::PEScene(){
	m_width = 0;
	m_height = 0;
	m_drawFunc = 0;
}

PEScene::~PEScene(){
	glfwDestoryWindow(m_pWindow);
	glfwTerminate();	
}

PScene * PEScene::createWithSize(string name, int width, int height)
{
	PEScene *scene = new PEScene();
	if(scene->initWithSize(width, height)){
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
	return true;
}

void PEScene::start()
{
	while(!glfwWindowShouldClose()){
		this->draw();
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}

void PEScene::draw()
{
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

int PEScene::Width()
{
	return m_width;
}

int PEScene::Height()
{
	return m_height;
}




