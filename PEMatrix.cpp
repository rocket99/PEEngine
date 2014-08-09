#include "PEMatrix.h"

PEMatrix::PEMatrix(int row, int col)
{
	m_row = row;
	m_col = col;
	m_data =(float *)malloc(sizeof(float *)*m_row*m_col);
}

PEMatrix::~PEMatrix()
{
	if(NULL != m_data){
		free(m_data);
	}
}

inline int PEMatrix::ID(int row, int col)
{
	if(row >= m_row || col >= m_col){
		PELog("Invalid matrix index!\n");
	}
	return col*m_row + row;
}

float PEMatrix::Elm(int row, int col)
{
	PE_Assert(row<m_row && col<m_col, "error: row >= max_row || col >= max_col");
	return m_data(ID(row, col));
}

void PEMatrix::setElm(int row, int col, float value)
{
	PE_Assert(row<m_row && col<m_col, "error: row >= max_row || col >= max_col");
	m_data[ID(row, col)] = value;
}
