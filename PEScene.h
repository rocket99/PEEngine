#ifndef 	__PEScene_H__
#define 	__PEScene_H__

#include "Base/PEObject.h"
#include "Shader/PEShaderManager.h"
#include "TestScene.h"

class PEScene: public PEObject
{
public:
	PEScene();
	~PEScene();
	static PEScene *createWithSize(string name, int width, int height);
	bool initWithSize(string name, int width, int height);
	void start();
	int Width();
	int Height();
private:
	string m_name;
	GLint m_width, m_height;
	GLFWwindow *m_pWindow;
	void drawFBO();
	void draw();
	GLuint m_colorTex, m_depthTex, m_fbo;
	void setFrameBuffer();

	void setGLPrograms();

	TestScene *m_scene;
};


#endif


