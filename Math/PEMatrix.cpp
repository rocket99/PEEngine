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

int PEMatrix::getRowNum(){
	return m_row;
}

int PEMatrix::getColumnNum(){
	return m_col;
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
	assert(row<m_row && col<m_col);
	return m_data[ID(row, col)];
}

void PEMatrix::setElm(int row, int col, float value)
{
	assert(row<m_row && col<m_col);
	m_data[ID(row, col)] = value;
}

void PEMatrix::display()
{
	printf("(row x col):%d x %d\n", m_row, m_col);
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<m_col; ++j){
			printf("%8.3f ", m_data[ID(i, j)]); 
		}
		printf("\n");
	}
}

void PEMatrix::displayRow(int row)
{
	if(row >= m_row)
		return;
	printf("row[%d]:\n", row);
	for(int i=0; i<m_col; ++i){
		printf("%8.3f ", m_data[ID(row, i)]);
	}
	printf("\n");
}

void PEMatrix::displayColumn(int col)
{
	if(col >= m_col)
		return;
	printf("col[%d]:\n", col);
	for(int i=0; i<m_row; ++i){
		printf("\t%8.3f,\n", m_data[ID(i, col)]);
	}
	printf("\n");
}

void PEMatrix::operator = (PEMatrix &mat)
{
	free(m_data);
	m_row = mat.getRowNum();
	m_col = mat.getColumnNum();
	m_data = (float *)malloc(sizeof(float)*m_row*m_col);
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<m_col; ++j){
			m_data[ID(i, j)] = mat.Elm(i, j);
		}
	}
}

void PEMatrix::operator * (float scale)
{
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<m_col; ++j){
			m_data[ID(i, j)] *= scale;
		}
	}
}

PEMatrix *PEMatrix::operator + (PEMatrix &mat)
{
	if(mat.getRowNum()!=m_row || mat.getColumnNum()!=m_col){
		return NULL;
	}
	PEMatrix *newMat = new PEMatrix(mat.getRowNum(), mat.getColumnNum());
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<m_col; ++j){
			newMat->setElm(i, j, mat.Elm(i,j)+m_data[ID(i, j)]);
		}
	}
	return newMat;
}

PEMatrix *PEMatrix::operator - (PEMatrix &mat)
{
	if(mat.getRowNum()!=m_row || mat.getColumnNum()!=m_col){
		return NULL;
	}
	PEMatrix *newMat = new PEMatrix(mat.getRowNum(), mat.getColumnNum());
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<m_col; ++j){
			newMat->setElm(i, j, -mat.Elm(i,j)+m_data[ID(i, j)]);
		}
	}
	return newMat;
}

PEMatrix *PEMatrix::complement(int row, int col)
{
	if(row >= m_col || col >= m_col){
		PELog("there is must be row<max_row && col<max_col");
		return NULL;
	}
	PEMatrix *retMat = new PEMatrix(m_row-1, m_col-1);
	int i1 = 0, j1 = 0;
	for(int i0=0; i0<m_row; ++i0){
		if(i0 == row){
			continue;
		}
		j1=0;
		for(int j0=0; j0<m_col; ++j0){
			if(j0 == col){
				continue;
			}	
			retMat->setElm(i1, j1, m_data[ID(i0, j0)]);
			++ j1;
		}
		++ i1;
	}
	return retMat;
}

float PEMatrix::morel()
{
	if(m_row != m_col){
		PELog("row != column");
		return 0;
	}
	float sum = 0.0;
	if(m_row == 1){
		sum = Elm(0, 0);
	}else{
		for(int i=0; i<m_col; ++i){
			PEMatrix *mat = this->complement(0, i);
			sum = i%2==0 ? sum + Elm(0, i)*mat->morel() : sum - Elm(0, i)*mat->morel();
			delete mat;
		}
	}
	return sum;
}

PEMatrix *PEMatrix::IdentityMat(int rank)
{
	PEMatrix *mat = new PEMatrix(rank, rank);
	for(int i=0; i<rank; ++i){
		for(int j=0; j<rank; ++j){
			if(i==j){
				mat->setElm(i, j, 1.0);
			}else{
				mat->setElm(i, j, 0.0);
			}
		}
	}
	return mat;
}

void PEMatrix::exchangeRow(int row0, int row1)
{
	for(int i=0; i<m_col; ++i){
		float tmp = m_data[ID(row0, i)];
		m_data[ID(row0, i)] = m_data[ID(row1, i)];
		m_data[ID(row1, i)] = tmp;
	}
}

void PEMatrix::exchangeColumn(int col0, int col1)
{
	for(int i=0; i<m_row; ++i){
		float tmp = m_data[ID(i, col0)];
		m_data[ID(i, col0)] = m_data[ID(i, col1)];
		m_data[ID(i, col1)] = tmp;
	}
}

PEMatrix *PEMatrix::inverse()
{
	PEMatrix mat;
	mat = *this;
	PEMatrix *inv = PEMatrix::IdentityMat(m_row);
	for(int i=0; i<m_row; ++i){
		if(mat.Elm(i, i) == 0.0){
			for(int j=i+1; j<m_row; ++j){
				if(mat.Elm(j, i) != 0){
					mat.exchangeRow(i, j);
					inv->exchangeRow(i, j);
					break;
				}
			}
		}
		float f = mat.Elm(i, i);
		for(int j=0; j<m_col; ++j){
			mat.setElm(i, j, mat.Elm(i, j)/f);
			inv->setElm(i, j, inv->Elm(i, j)/f);
		}
		for(int r=0; r<m_row; ++r){
			if(r == i){
				continue;
			}
			float a = mat.Elm(r, i)/mat.Elm(i, i);
			for(int k=0; k<m_col; ++k){
				mat.setElm(r, k, mat.Elm(r, k)-a*mat.Elm(i, k));
				inv->setElm(r, k, inv->Elm(r, k)-a*inv->Elm(i, k));
			}
		}
	}
	return inv;
}

void PEMatrix::transfers()
{
	float *buf = (float *)malloc(sizeof(float) * m_row * m_col);
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<m_col; ++j){
			buf[ID(i, j)] = m_data[ID(j, i)];
		}
	}
	for(int i=0; i<m_row*m_col; ++i){
		m_data[i] = buf[i];
	}
	free(buf);
	int tmp = m_row;
	m_row = m_col;
	m_col = tmp;
}

PEMatrix *PEMatrix::cross(PEMatrix &mat)
{
	if(m_col != mat.getRowNum()){
		return NULL;
	}
	PEMatrix *result = new PEMatrix(m_row, mat.getColumnNum());
	for(int i=0; i<m_row; ++i){
		for(int j=0; j<mat.getColumnNum(); ++j){
			result->setElm(i, j, 0.0);
			for(int k=0; k<m_col; ++k){
				float tmp = result->Elm(i, j);
				result->setElm(i, j, tmp+this->Elm(i, k)*mat.Elm(k, j));
			}
//			PELog("mat[%d %d] = %.3f", i, j, result->Elm(i, j));
		}
	}
	return result;
}




