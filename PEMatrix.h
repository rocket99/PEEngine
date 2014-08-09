#ifndef __PEMatrix_H__
#define __PEMatrix_H__

#include "PEPrefix.h"

class PEMatrix
{
	public:
		PEMatrix():m_row(0), m_col(0),m_data(NULL){};
		PEMatrix(int row, int col);
		~PEMatrix();

		Elm(int row, int col);
		setElm(int row, int col, float value);
	protected:
		int m_col, m_row;
	private:
		float *m_data;
		int ID(int row, int col);
		
}


#endif

