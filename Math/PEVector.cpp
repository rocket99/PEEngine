#include "PEVector.h"

PEVector::PEVector(int num)
{
	m_num = num;
	m_data = new float[num];
	for(int i=0; i<m_num; ++i){
		m_data[i] = 0.0;
	}	
}

PEVector::PEVector(const PEVector &vec)
{
    m_num = vec.elmNum();
    m_data = new float[m_num];
    for(int i=0; i<m_num; ++i){
        m_data[i] = vec[i];
    }
}

PEVector::~PEVector()
{
	delete [] m_data;
}

int PEVector::elmNum()
{
	return m_num;
}

int PEVector::elmNum() const
{
	return m_num;
}

float &PEVector::operator[](int idx)
{
	
	return m_data[idx];
}

float &PEVector::operator[](int idx) const
{
	return m_data[idx];
}

void PEVector::operator = (const PEVector &vec)
{
	if(vec.elmNum() != m_num){
		delete [] m_data;
		m_num = vec.elmNum();
		m_data = new float[m_num];
	}
	for(int i=0; i<m_num; ++i){
		m_data[i] = vec[i];
	}
}

PEVector operator + (const PEVector &A, const PEVector &B)
{
	int r = A.elmNum() > B.elmNum() ? A.elmNum() : B.elmNum();
	PEVector result(r);
	for(int i=0; i<result.elmNum(); ++i){	
		if(i >= A.elmNum()){	
			result[i] = B[i];
			continue;
		}
		if(i >= B.elmNum()){
			result[i] = A[i];
			continue;
		}
		result[i] = A[i] + B[i]; 	
	}	
	return result;
}

PEVector operator - (const PEVector &A, const PEVector &B)
{
	int r = A.elmNum() > B.elmNum() ? A.elmNum() : B.elmNum();
	PEVector result(r);
	for(int i=0; i<result.elmNum(); ++i){
		if(i >= A.elmNum()){
			result[i] = -B[i];
			continue;
		}
		if(i>= B.elmNum()){
			result[i] = A[i];
			continue;
		}
		result[i] = A[i] - B[i];		
	}	
	return result;
}

PEVector operator * (const PEVector &A, const PEVector &B)
{
	int r = A.elmNum() > B.elmNum() ? A.elmNum() : B.elmNum();
	PEVector result(r);
	for(int i=0; i<result.elmNum(); ++i){
		if(i >= A.elmNum()){
			result[i] = 0.0 - B[i];
			continue;
		}
		if(i>= B.elmNum()){
			result[i] = A[i];
			continue;
		}
		result[i] = A[i] * B[i];
	}	
	return result;	
}

PEVector operator / (const PEVector &A, const PEVector &B)
{
	int r = A.elmNum() > B.elmNum() ? A.elmNum() : B.elmNum();
	PEVector result(r);
	for(int i=0; i<result.elmNum(); ++i){
		if(i >= A.elmNum()){
			result[i] = 0.0 - B[i];
			continue;
		}
		if(i>= B.elmNum()){
			result[i] = A[i];
			continue;
		}
		result[i] = A[i] / B[i];
	}
	return result;
}

bool PEVector::operator == (const PEVector &vec)
{
    if (elmNum() != vec.elmNum()) {
        return false;
    }
    for(int i=0; i<m_num; ++i){
        if(m_data[i] != vec[i]){
            return false;
        }
    }
    return true;
}

bool PEVector::operator != (const PEVector &vec)
{
    return !(*this == vec);
}

void PEVector::display()
{
	for(int i=0; i<m_num; ++i){
		printf("%.3f, ", m_data[i]);
	}
	printf("\n");
}

void PEVector::setValues(int num, ...)
{
    if (num >= m_num) {
        return;
    }
    va_list va;
    va_start(va, num);
    for(int i=0; i<num; ++i){
        m_data[i] = (float)va_arg(va, double);
    }
    va_end(va);
}



