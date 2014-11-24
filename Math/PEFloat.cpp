#include "PEFloat.h"

PEfloat::PEfloat()
{
	m_content = new char[100];
	memset(m_content, 0, 100*sizeof(char));
}

PEfloat::~PEfloat()
{
	delete [] m_content;
}

void PEfloat::operator = (float A){
	sprintf(m_content, "%.5f", A);
}

void PEfloat::display() 
{
	
}


