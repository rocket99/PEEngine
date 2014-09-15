//
//
//
#ifndef __TestScene_H__
#define __TestScene_H__

#include "PEEngine.h"

class TestScene:public PELayer3D
{
public:
	static TestScene *create(const Size3D &size);
	bool initWithSize(const Size3D &size);

private:

};


#endif
