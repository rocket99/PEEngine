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
	light->Specular()=  ColorRGBA(0.9, 0.9, 0.9, 1.0);
	light->setCamera();
	this->getCamera()->World() = size;

	PERect *plane= PERect::create(1000, 1000);
	plane->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
	plane->Position() = Point3D(0.0, 0.0, 0.0);
	plane->Program0() = PEShaderManager::Instance()->getProgramForKey("vertColor");
	plane->Program1() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
	plane->Color() = ColorRGBA(0.4, 0.4, 0.2, 1.0);
	plane->Material().ambient = ColorRGBA(0.1, 0.1, 0.1, 1.0);
	plane->Material().diffuse = ColorRGBA(0.5, 0.5, 0.5, 1.0);
	plane->Material().specular = ColorRGBA(0.8, 0.3, 0.2, 1.0);
	plane->Material().emission = ColorRGBA(0.3, 0.3, 0.2, 1.0);
	plane->Texture() = tex->Texture();
	this->addChild(plane);
	
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			PESphereSurface *sphere = PESphereSurface::create(40, 40, 40);	
			sphere->Program0() = PEShaderManager::Instance()->getProgramForKey("vertColor");
			sphere->Program1() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
			sphere->Position() = Point3D(-400+i*200, 100.0, -400+j*200);
			sphere->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
			sphere->Color() = ColorRGBA(0.5, 0.4, 0.1, 1.0);
			sphere->Material().emission = ColorRGBA(0.2, 0.4, 0.6, 1.0);
			sphere->Material().ambient = ColorRGBA(0.2, 0.3, 0.1, 1.0);
			sphere->Material().diffuse = ColorRGBA(0.4, 0.4, 0.4, 1.0);
			sphere->Material().specular = ColorRGBA(0.9, 0.5, 0.3, 1.0);
			this->addChild(sphere);
		}
	}
//显示缓冲
	PERect *rect = PERect::create(600, 600);
	rect->Program1() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
	rect->Texture() = PETextureManager::Instance()->DepthTex();
//	this->addChild(rect);
	return true;
}

void TestScene::update(){}

void TestScene::setKeyboardEvent()
{
	PEKeyboardEvent *w_event = new PEKeyboardEvent(GLFW_KEY_W);
	w_event->setSceneIn(m_pWindow);
	w_event->setPressLastFunction(std::bind(&PECamera::moveForward, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(w_event);

	PEKeyboardEvent *s_event = new PEKeyboardEvent(GLFW_KEY_S);
	s_event->setSceneIn(m_pWindow);
	s_event->setPressLastFunction(std::bind(&PECamera::moveBackward, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(s_event);
	
	PEKeyboardEvent *a_event = new PEKeyboardEvent(GLFW_KEY_A);
	a_event->setSceneIn(m_pWindow);
	a_event->setPressLastFunction(std::bind(&PECamera::moveLeft, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(a_event);
	
	PEKeyboardEvent *d_event = new PEKeyboardEvent(GLFW_KEY_D);
	d_event->setSceneIn(m_pWindow);
	d_event->setPressLastFunction(std::bind(&PECamera::moveRight, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(d_event);
}



