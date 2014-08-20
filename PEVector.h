#ifndef __PEVector_H__
#define __PEVector_H__
#include "PEPrefix.h"

class PEVector
{
public:
	PEVector(int num);
//	PEVector(int num, ...);
	~PEVector();
	int elmNum(); 
	float &operator [] (int idx);
	float &operator [] (int idx) const;
	void operator = (PEVector &vec);
	friend PEVector operator + (PEVector &A, PEVector &B);
	friend PEVector operator - (PEVector &A, PEVector &B);
	friend PEVector operator * (PEVector &A, PEVector &B);
	void display();
private:
	int m_num;
	float *m_data;
};

#endif



