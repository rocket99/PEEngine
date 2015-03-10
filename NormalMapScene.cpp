//2015-2-8
//
//created by maomeng
//
#include "NormalMapScene.h"

NormalMapScene::NormalMapScene()
{

}

NormalMapScene::~NormalMapScene()
{

}

PEScene *NormalMapScene::Scene(const Size3D &size)
{
	PEScene *scene = PEScene::createWithSize("normal map", size.x, size.y);
	NormalMapScene *layer = NormalMapScene::createWithSize(size);
	scene->addChild(layer);
	return scene;
}

NormalMapScene *NormalMapScene::createWithSize(const Size3D &size)
{
	NormalMapScene *layer = new NormalMapScene;
	if(layer && layer->initWithSize(size)){
		return layer;
	}
	delete layer;
	return nullptr;
}

bool NormalMapScene::initWithSize(const Size3D &size)
{
	if(false == PELayer3D::initWithSize(size)){
		return false;
	}
	m_program = PEShaderManager::Instance()->getProgramForKey("normal_map");
	PETexture *tex0 = PETexture::create("../tank/tank_zxhp_heibao_body.png",
											PETexture::PicType::PNG_PIC);
	PETexture *tex1 = PETexture::create("../tank/tank_zxhp_heibao_body_normal.png", 
											PETexture::PicType::PNG_PIC);
	m_texture = tex0->Texture();
	m_normalTex = tex1->Texture();
	return true;
}

void NormalMapScene::draw()
{
	const GLfloat coords[] = {
		-47, -72, 0.0, 
		-47,  72, 0.0,
		 47,  72, 0.0,
		 47, -72, 0.0,
	};	
	const GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 0.3f,
		1.0f, 1.0f, 0.0f, 0.2f,
		0.0f, 1.0f, 0.0f, 0.1f,
		0.0f, 1.0f, 1.0f, 0.3f,
	};
	const GLfloat texCoords[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	};
	glUseProgram(m_program);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	GLint loc = glGetUniformLocation(m_program, "u_colorTex");
	if(loc >= 0){
		glUniform1i(loc, 0);
		glActiveTexture(GL_TEXTURE0);	
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	loc = glGetUniformLocation(m_program, "u_normalTex");
	if(loc >=0){
		glUniform1i(loc, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_normalTex);
	}

	loc = glGetUniformLocation(m_program, "u_space");
	if(loc >= 0){
		glUniform3f(loc, m_size.x, m_size.y, m_size.z);
	}
	loc = glGetUniformLocation(m_program, "u_offset");
	if(loc >= 0){
		glUniform3f(loc, 80, -150, 0.0);
	}
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, coords);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	

/*	loc = glGetUniformLocation(m_program, "u_offset");
	if(loc >= 0){
		glUniform3f(loc, 100, -200, -10.0);
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);*/

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}


