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

	PETexture *tex = PETexture::create("../tank/tank_hp_heibaoII_body_normal.png", PETexture::PicType::PNG_PIC);
//	PETexture *tex = PETexture::create("../user.png", PETexture::PicType::PNG_PIC);
	PELog("tex width= %d, height=%d\n", tex->Width(), tex->Height());
	PERect *bound  = PERect::create(tex->Width(), tex->Height());
	bound->Texture() = tex->Texture(); 
	bound->Program1() = PEShaderManager::Instance()->getProgramForKey("normal");
	this->addChild(bound);

//显示缓冲
	PERect *rect = PERect::create(800, 800);
	rect->Rotate(Point3D(1.0, 0.0, 0.0), 90.0);
	rect->Position() = Point3D(0.0, 600.0, 0.0);
	rect->Program1() = PEShaderManager::Instance()->getProgramForKey("vert_tex");
	rect->Texture() = PETextureManager::Instance()->DepthTex();
	this->addChild(rect);

	this->setKeyboardEvent();



	return true;
}   

void TestScene::update(){
}

void TestScene::setKeyboardEvent()
{
	PEKeyboardEvent *w_event = new PEKeyboardEvent(GLFW_KEY_W);
	w_event->setPressLastFunction(std::bind(&PECamera::moveForward, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(w_event);

	PEKeyboardEvent *s_event = new PEKeyboardEvent(GLFW_KEY_S);
	s_event->setPressLastFunction(std::bind(&PECamera::moveBackward, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(s_event);
	
	PEKeyboardEvent *a_event = new PEKeyboardEvent(GLFW_KEY_A);
	a_event->setPressLastFunction(std::bind(&PECamera::moveLeft, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(a_event);
	
	PEKeyboardEvent *d_event = new PEKeyboardEvent(GLFW_KEY_D);
	d_event->setPressLastFunction(std::bind(&PECamera::moveRight, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(d_event);
	
	PEKeyboardEvent *e_event = new PEKeyboardEvent(GLFW_KEY_E);
	e_event->setPressLastFunction(std::bind(&PECamera::moveUp, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(e_event);
	
	PEKeyboardEvent *r_event = new PEKeyboardEvent(GLFW_KEY_R);
	r_event->setPressLastFunction(std::bind(&PECamera::moveDown, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(r_event);
	
	PEKeyboardEvent *left_event = new PEKeyboardEvent(GLFW_KEY_LEFT);
	left_event->setPressLastFunction(std::bind(&PECamera::positiveRotate, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(left_event);
	
	PEKeyboardEvent *right_event = new PEKeyboardEvent(GLFW_KEY_RIGHT);
	right_event->setPressLastFunction(std::bind(&PECamera::nagitiveRotate, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(right_event);

	PEKeyboardEvent *up_event = new PEKeyboardEvent(GLFW_KEY_UP);
	up_event->setPressLastFunction(std::bind(&PECamera::lookUp, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(up_event);

	PEKeyboardEvent *down_event = new PEKeyboardEvent(GLFW_KEY_DOWN);
	down_event->setPressLastFunction(std::bind(&PECamera::lookDown, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(down_event);
	
	PEKeyboardEvent *z_event = new PEKeyboardEvent(GLFW_KEY_Z);
	z_event->setPressLastFunction(std::bind(&PECamera::lookLeft, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(z_event);
	
	PEKeyboardEvent *x_event = new PEKeyboardEvent(GLFW_KEY_X);
	x_event->setPressLastFunction(std::bind(&PECamera::lookRight, this->getCamera()));
	PEKeyboardManager::getInstance()->addKeyboardEvent(x_event);
}

void TestScene::draw()
{
	PENode::draw();
	const GLfloat coords[] = {
		-100.0, -100.0, 0.0, -100.0, 100.0, 0.0, 100.0, 100.0, 0.0, 100.0, -100.0, 0.0,
	};
	const GLubyte colors[] = {
		255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 128, 128, 0, 128,
	};	
	const GLfloat texCoords[] = {
		0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
	};
	GLuint program = PEShaderManager::Instance()->getProgramForKey("vert_color");
	glUseProgram(program);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, coords);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLint loc = glGetUniformLocation(program, "u_position");
	if(loc >= 0){
		glUniform3f(loc, 0.0f, 0.0f, 0.0f);
	}
	loc = glGetUniformLocation(program, "u_space");
	if(loc >= 0){
		glUniform3f(loc, m_size.x, m_size.y, m_size.x);
	}	

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

