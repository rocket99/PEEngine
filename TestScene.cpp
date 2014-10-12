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
	PETexture *tex = PETexture::create("15182.jpg", PETexture::PicType::JPG_PIC);
	

	PELight *light = this->getLightSource();
	light->Fovy() = 30.0;
	light->Shininess() = 7.0;
	light->Position() = Point3D(0.0, 700.0, 0.0);
	light->Direction() = Point3D(0.0, -1.0, 0.0);
	light->Ambient() = ColorRGBA(0.1, 0.1, 0.1, 1.0); 
	light->Diffuse() = ColorRGBA(0.4, 0.4, 0.6, 0.5);
	light->Specular()=  ColorRGBA(0.7, 0.7, 0.6, 1.0);
	light->setCamera();
	this->getCamera()->World() = size;

	PERect *plane= PERect::create(1000, 1000);
	plane->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
	plane->Position() = Point3D(0.0, 0.0, 0.0);
	plane->Program1() = PEShaderManager::Instance()->getProgramForKey("vertColor");
//	plane->Program1() = PEShaderManager::Instance()->getProgramForKey("light");
	plane->Color() = ColorRGBA(0.4, 0.4, 0.2, 1.0);
	plane->Material().ambient = ColorRGBA(0.1, 0.1, 0.1, 1.0);
	plane->Material().diffuse = ColorRGBA(0.5, 0.5, 0.5, 1.0);
	plane->Material().specular = ColorRGBA(0.8, 0.3, 0.2, 1.0);
	plane->Material().emission = ColorRGBA(0.3, 0.3, 0.2, 1.0);
	plane->Texture() = 0;
	this->addChild(plane);
	
	for(int i=0; i<11; ++i){
		for(int j=0; j<11; ++j){
			PESphere *sphere = PESphere::create(40, 40, 40);	
			sphere->Program1() = PEShaderManager::Instance()->getProgramForKey("vertColor");
//			sphere->Program1() = PEShaderManager::Instance()->getProgramForKey("light");
			sphere->Position() = Point3D(-500+i*100, 200.0, -500+j*100);
			sphere->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
			sphere->Color() = ColorRGBA(0.5, 0.4, 0.1, 1.0);
			sphere->Material().emission = ColorRGBA(0.2, 0.4, 0.6, 1.0);
			sphere->Material().ambient = ColorRGBA(0.2, 0.3, 0.1, 1.0);
			sphere->Material().diffuse = ColorRGBA(0.4, 0.4, 0.4, 1.0);
			sphere->Material().specular = ColorRGBA(0.9, 0.5, 0.3, 1.0);
			this->addChild(sphere);
		}
	}
	return true;
}

void TestScene::update()
{
	static float a = 0.0;
	this->getCamera()->WorldPos() = Point3D(1000.0*cos(a/180.0*M_PI), 1000.0, 1000.0*sin(a/180.0*M_PI));
	this->getCamera()->upDirect() = Point3D(0.0, 1.0, 0.0);
	this->getCamera()->WorldFocus() = Point3D(0.0, 0.0, 0.0);
	a += 0.5;
}


