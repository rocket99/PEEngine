#ifndef 	__PEScene_H__
#define 	__PEScene_H__

#include "PEPrefix.h"

class PEScene
{
public:
	PEScene();
	~PEScene();
	static createWithSize(string name, int width, int height);
	bool initWithSize(string name, int width, int height);
	
	void start();

	int Width();
	int Height();

private:
	string m_name;
	GLint m_width, m_height;
	GLFWwindow *m_pWindow;
	void draw();
};


#endif


