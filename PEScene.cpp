//
// PEScene.cpp
//

#include "PEScene.h"

PEScene::PEScene()
{
	m_width = 0;
	m_height = 0;
}

PEScene::~PEScene()
{
	
}

PScene * PEScene::createWithSize(int width, int height)
{
	PEScene *scene = new PEScene();
	if(scene->initWithSize(width, height)){
		return scene;
	}
	delete scene;
	return NULL;
}

bool PEScene::initWithSize(int width, int height)
{
	m_width = width;
	m_height = height;
	int ret = glfwInit();
	if(ret == 0){
		return false;
	}
	
	return true;
}

int PEScene::Width()
{
	return m_width;
}

int PEScene::Height()
{
	return m_height;
}
