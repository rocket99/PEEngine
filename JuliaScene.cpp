//created 2015-2-16
//by maomeng
//

#include "JuliaScene.h"

JuliaScene::JuliaScene()
{}

JuliaScene::~JuliaScene()
{}

PEScene *JuliaScene::Scene(const Size3D &size)
{
	PEScene *scene = PEScene::createWithSize("Julia", size.x, size.y);
	JuliaScene *layer = JuliaScene::createWithSize(size);
	if(layer!= nullptr && scene != nullptr){
		scene->addChild(layer);
		return scene;
	}
	return nullptr;
}

JuliaScene *JuliaScene::createWithSize(const Size3D &size)
{
	JuliaScene *layer = new JuliaScene;
	if(layer->initWithSize(size)){
		layer->autoRelease();
		return layer;
	}
	delete layer;
	return nullptr;
}

bool JuliaScene::initWithSize(const Size3D &size)
{
	if(!PELayer3D::initWithSize(size)){
		return false;
	}

	return true;
}

void JuliaScene::draw()
{
	GLuint program = PEShaderManager::Instance()->getProgramForKey("julia");
	glUseProgram(program);

	const GLfloat points[] = {
		-1.0, -1.0, 0.0,
		-1.0,  1.0, 0.0,
		 1.0,  1.0, 0.0,
		 1.0, -1.0, 0.0,
	};
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, points);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableVertexAttribArray(0);
}




