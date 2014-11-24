#ifndef __PEFloat_H__
#define __PEFloat_H__

#include "../PEPrefix.h"

class PEfloat
{
public:
	PEfloat();
	~PEfloat();
	void operator = (float A);
	void display();
private:
	char *m_content;
	int m_pointIdx;//小数点位置
};

#endif
