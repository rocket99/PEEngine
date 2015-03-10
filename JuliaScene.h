//created 2015-2-16
//by maomeng
//
//
#ifndef __JuliaScene_H__
#define __JuliaScene_H__

#include "PEEngine.h"

class JuliaScene:public PELayer3D
{
	public:
	JuliaScene();
	~JuliaScene();

	static PEScene *Scene(const Size3D &size);
	static JuliaScene * createWithSize(const Size3D &size);
	bool initWithSize(const Size3D &size);
	
	void draw();
	protected:
	GLuint m_program;

};


#endif
