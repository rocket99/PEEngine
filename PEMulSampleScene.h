//
//
//
//
//
#ifndef	__PEMulSampleScene_H__
#define __PEMulSampleScene_H__

#include "PEPrefix.h"
#include "Base/PENode.h"
#include "Render/PEShaderManager.h"
#include "Render/PEShaders.h"
#include "Base/PELayer3D.h"
#include "PEKeyboardManager.h"
#include "PETextureManager.h"

class PEMulSampleScene: public PENode
{
public:
	PEMulSampleScene();
	~PEMulSampleScene();
	static PEMulSampleScene *createWithSize(string name, int width, int height);
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
	void saveViewToPicture();
	void checkKeyboardInput();
	PEKeyboardEvent *m_event;

	void displayHardwareInfo();
};



#endif


