#ifndef 	__PEScene_H__
#define 	__PEScene_H__

#include "PEPrefix.h"

class PEScene
{
public:
	PEScene();
	~PEScene();
	static createWithSize(int width, int height);
	bool initWithSize(int width, int height);

	int Width();
	int Height();

private:
	GLint m_width, m_height;
	GLFWwindow *m_pWindow;
	
};


#endif


