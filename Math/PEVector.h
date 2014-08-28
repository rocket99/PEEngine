#ifndef __PEVector_H__
#define __PEVector_H__
#include "PEPrefix.h"
class PEVector
{
public:
    PEVector():m_num(0), m_data(NULL){};
	PEVector(int num);
    PEVector(const PEVector &vec);
	~PEVector();
	int elmNum();
    int elmNum() const;
	float &operator [] (int idx);
	float &operator [] (int idx) const;
	void operator = (const PEVector &vec);
    bool operator == (const PEVector &vec);
    bool operator != (const PEVector &vec);
	friend PEVector operator + (const PEVector &A, const PEVector &B);
	friend PEVector operator - (const PEVector &A, const PEVector &B);
	friend PEVector operator * (const PEVector &A, const PEVector &B);
	friend PEVector operator / (const PEVector &A, const PEVector &B);
    friend PEVector operator * (const PEVector &A, float scale);
    void display();
    void setValues(int num, ...);
private:
	int m_num;
	float *m_data;
};

#endif

