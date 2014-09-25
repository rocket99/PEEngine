#include "TestScene.h"

TestScene *TestScene::create(const Size3D &size)
{
	TestScene *scene = new TestScene();
	if(scene->initWithSize(size)){
		return scene;
	}
	delete scene;
	return NULL;
}

bool TestScene::initWithSize(const Size3D &size)
{
	if(!PELayer3D::initWithSize(size)){
		return false;
	}
	
	PESphere *sphere = PESphere::create(40, 40, 300);
	sphere->Program1() = PEShaderManager::Instance()->getProgramForKey("vertColor");
	sphere->Color() = ColorRGBA(0.5, 0.4, 0.1, 1.0);

	this->addChild(sphere, "sphere");
	return true;
}


