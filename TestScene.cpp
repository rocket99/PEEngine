#include "TestScene.h"

PEScene *TestScene::Scene(const Size3D &size)
{
	PEScene *scene = PEScene::createWithSize("Test", size.x, size.y);
	TestScene *layer = TestScene::create(size);
	if(NULL == layer){
		return NULL;
	}
	scene->addChild(layer);
	return scene;
}

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
	light->Fovy() =40.0;
	light->Shininess() = 2.3;
	light->Position() = Point3D(0.0, 600.0, 0.0);
	light->Direction() = Point3D(0.3, -1.0, 0.1);
	light->Ambient() = ColorRGBA(0.1, 0.2, 0.05, 1.0); 
	light->Diffuse() = ColorRGBA(0.3, 0.3, 0.2, 0.5);
	light->Specular()=  ColorRGBA(0.9, 0.9, 0.9, 1.0);
	light->setCamera();

	this->getCamera()->World() = size;
	this->getCamera()->zNear() = 0.001;

	PERect *plane= PERect::create(1000, 1000);
	plane->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
	plane->Position() = Point3D(0.0, 0.0, 0.0);
	plane->Program0() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
	plane->Program1() = PEShaderManager::Instance()->getProgramForKey("shadow");
	plane->Color() = ColorRGBA(0.4, 0.4, 0.2, 1.0);
	plane->Material().ambient = ColorRGBA(0.2, 0.2, 0.1, 1.0);
	plane->Material().diffuse = ColorRGBA(0.5, 0.5, 0.5, 1.0);
	plane->Material().specular = ColorRGBA(0.3, 0.6, 0.6, 1.0);
	plane->Material().emission = ColorRGBA(0.3, 0.2, 0.2, 1.0);
	plane->Texture() = tex->Texture();
	this->addChild(plane);
	
/*	for(int a=0; a<3; ++a){
		for(int i=0; i<5; ++i){
			for(int j=0; j<5; ++j){
				PEBoxNode *box = PEBoxNode::createWithSize(Point3D(100, 30, 100));	
				box->Program0() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
				box->Program1() = PEShaderManager::Instance()->getProgramForKey("shadow");
				box->Position() = Point3D(-400+i*200+ a*50.0, 100.0+a*100.0, -400+j*200 + a*70.0);
				box->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
				box->Color() = ColorRGBA(0.5, 0.4, 0.1, 1.0);
				box->Material().emission = ColorRGBA(0.3, 0.25, 0.2, 1.0);
				box->Material().ambient = ColorRGBA(0.2, 0.3, 0.1, 1.0);
				box->Material().diffuse = ColorRGBA(0.4, 0.4, 0.4, 1.0);
				box->Material().specular = ColorRGBA(0.8, 0.7, 0.2, 1.0);
				box->Texture() = tex->Texture();
				this->addChild(box);
			}
		}
	}
*/
//显示缓冲
/*	PERect *rect = PERect::create(800, 800);
	rect->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
	rect->Position() = Point3D(0.0, 600.0, 0.0);
	rect->Program1() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
	rect->Texture() = PETextureManager::Instance()->DepthTex();
	this->addChild(rect);
*/
	this->setKeyboardEvent();
	return true;
}   

void TestScene::update(){
//	PERealNode *node = static_cast<PERealNode *>(this->getChildByName("box"));
//	m_motion.LorenzMotion(0.001);
//	node->Position() = m_motion.Position();
}

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
	
	PEKeyboardEvent *e_event = new PEKeyboardEvent(GLFW_KEY_E);
	e_event->setSceneIn(m_pWindow);
	e_event->setPressLastFunction(std::bind(&PECamera::moveUp, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(e_event);
	
	PEKeyboardEvent *r_event = new PEKeyboardEvent(GLFW_KEY_R);
	r_event->setSceneIn(m_pWindow);
	r_event->setPressLastFunction(std::bind(&PECamera::moveDown, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(r_event);
	
	PEKeyboardEvent *left_event = new PEKeyboardEvent(GLFW_KEY_LEFT);
	left_event->setSceneIn(m_pWindow);
	left_event->setPressLastFunction(std::bind(&PECamera::positiveRotate, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(left_event);
	
	PEKeyboardEvent *right_event = new PEKeyboardEvent(GLFW_KEY_RIGHT);
	right_event->setSceneIn(m_pWindow);
	right_event->setPressLastFunction(std::bind(&PECamera::nagitiveRotate, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(right_event);

	PEKeyboardEvent *up_event = new PEKeyboardEvent(GLFW_KEY_UP);
	up_event->setSceneIn(m_pWindow);
	up_event->setPressLastFunction(std::bind(&PECamera::lookUp, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(up_event);

	PEKeyboardEvent *down_event = new PEKeyboardEvent(GLFW_KEY_DOWN);
	down_event->setSceneIn(m_pWindow);
	down_event->setPressLastFunction(std::bind(&PECamera::lookDown, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(down_event);
	
	PEKeyboardEvent *z_event = new PEKeyboardEvent(GLFW_KEY_Z);
	z_event->setSceneIn(m_pWindow);
	z_event->setPressLastFunction(std::bind(&PECamera::lookLeft, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(z_event);
	
	PEKeyboardEvent *x_event = new PEKeyboardEvent(GLFW_KEY_X);
	x_event->setSceneIn(m_pWindow);
	x_event->setPressLastFunction(std::bind(&PECamera::lookRight, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(x_event);
}


