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
	PELog("TestScene init.");

	PETexture *tex = PETexture::create("15182.jpg", PETexture::PicType::JPG_PIC);	
	PELight *light = this->getLightSource();
	light->Fovy() = 30.0;
	light->Shininess() = 7.0;
	light->Position() = Point3D(0.0, 1000.0, 0.0);
	light->Direction() = Point3D(0.0, -1.0, 0.0);
	light->Ambient() = ColorRGBA(0.1, 0.1, 0.1, 1.0); 
	light->Diffuse() = ColorRGBA(0.4, 0.4, 0.4, 0.5);
	light->Specular()=  ColorRGBA(0.9, 0.9, 0.9, 1.0);
	light->setCamera();
	this->getCamera()->World() = size;

	PERect *plane= PERect::create(1000, 1000);
	plane->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
	plane->Position() = Point3D(0.0, 0.0, 0.0);
	plane->Program0() = PEShaderManager::Instance()->getProgramForKey("vertColor");
	plane->Program1() = PEShaderManager::Instance()->getProgramForKey("light");
	plane->Color() = ColorRGBA(0.4, 0.4, 0.2, 1.0);
	plane->Material().ambient = ColorRGBA(0.1, 0.1, 0.1, 1.0);
	plane->Material().diffuse = ColorRGBA(0.5, 0.5, 0.5, 1.0);
	plane->Material().specular = ColorRGBA(0.3, 0.3, 0.2, 1.0);
	plane->Material().emission = ColorRGBA(0.3, 0.2, 0.2, 1.0);
	plane->Texture() = tex->Texture();
	this->addChild(plane);
	
/*	for(int i=0; i<5; ++i){
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
			sphere->Texture() = tex->Texture();
			this->addChild(sphere);
		}
	}
 */
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

void TestScene::setLightUniform()
{
	GLuint prog = PEShaderManager::Instance()->getProgramForKey("light");
	GLint index = glGetUniformLocation(prog, "u_light");
	printf("GLProgram %d light index %d\n", prog, index);
	index = glGetUniformBlockIndex(prog, "u_material");
	printf("GLProgram %d material index %d\n", prog, index);
	if(index == GL_INVALID_INDEX){
		printf("invalid index\n");
	}
	GLuint indices[7];
	const char *names[] = {"u_light.l_ambient", "u_light.l_diffuse",
					"u_light.l_specular", "u_light.l_position", "u_light.l_direction",
					"u_light.l_fovy", "u_light.l_shininess"};
	glGetUniformIndices(prog, 7, names, indices);
	printf("%d, %d, %d, %d, %d, %d, %d\n", indices[0], indices[1], indices[2], indices[3],
					indices[4], indices[5], indices[6]);
}



