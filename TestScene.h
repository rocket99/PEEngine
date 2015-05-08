//
//
//
#ifndef __TestScene_H__
#define __TestScene_H__

#include "PEEngine.h"

class TestScene:public PELayer3D
{
public:
	static PEScene *Scene(const Size3D &size);
	static PEMulSampleScene *mulSampleScene(const Size3D &size);
	static TestScene *create(const Size3D &size);
	bool initWithSize(const Size3D &size);	
	void update();
	void setGLFWwindow(GLFWwindow *window){
		m_pWindow = window;
	}
	void setKeyboardEvent();

	void draw();
private:
	GLFWwindow *m_pWindow;
	PEMotion m_motion;
};


#endif
