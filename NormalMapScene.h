//2015-2-8
//
//created by maomeng
//

#ifndef __NormalMapScene_H__
#define __NormalMapScene_H__
#include "PEEngine.h"

class NormalMapScene:public PELayer3D
{
	public:
		NormalMapScene();
		~NormalMapScene();

		static PEScene *Scene(const Size3D &size);
		static NormalMapScene *createWithSize(const Size3D &size);
		bool initWithSize(const Size3D &size);

		void draw();
	private:
		GLfloat *m_vertCoords;
		GLfloat *m_texCoords;

		GLuint m_program;
		GLuint m_texture, m_normalTex;
};


#endif

