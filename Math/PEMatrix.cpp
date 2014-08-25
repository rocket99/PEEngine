#include "PEMatrix.h"

PEMatrix::PEMatrix(int row, int col)
{
	m_row = row;
	m_col = col;
	m_data =(float *)malloc(sizeof(float)*m_row*m_col);
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

float &PEMatrix::Elm(int row, int col)
{
	assert(row<m_row && col<m_col);
	return m_data[ID(row, col)];
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

void PEMatrix::operator += (PEMatrix &mat)
{
    for(int i=0; i<m_row; ++i){
        if(i >= mat.getRowNum()){
            break;
        }
        for(int j=0; j<m_col; ++j){
            if(j >= mat.getColumnNum()){
                break;
            }
            Elm(i, j) += mat.Elm(i, j);
        }
    }
}

void PEMatrix::operator -= (PEMatrix &mat)
{
    for(int i=0; i<m_row; ++i){
        if(i >= mat.getRowNum()){
            break;
        }
        for(int j=0; j<m_col; ++j){
            if(j >= mat.getColumnNum()){
                break;
            }
            Elm(i, j) -= mat.Elm(i, j);
        }
    }
}

void PEMatrix::operator *= (PEMatrix &mat)
{
    for(int i=0; i<m_row; ++i){
        if(i >= mat.getRowNum()){
            break;
        }
        for(int j=0; j<m_col; ++j){
            if(j >= mat.getColumnNum()){
                break;
            }
            Elm(i, j) *= mat.Elm(i, j);
        }
    }
}

void PEMatrix::operator /= (PEMatrix &mat)
{
    for(int i=0; i<m_row; ++i){
        if(i >= mat.getRowNum()){
            break;
        }
        for(int j=0; j<m_col; ++j){
            if(j >= mat.getColumnNum()){
                break;
            }
            Elm(i, j) /= mat.Elm(i, j);
        }
    }
}

bool PEMatrix::operator == (PEMatrix &mat)
{
    if(m_row != mat.getRowNum() || m_col != mat.getColumnNum()){
        return false;
    }
    for (int i=0; i<m_row; ++i) {
        for(int j=0; j<m_col; ++j){
            if (Elm(i, j) != mat.Elm(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool PEMatrix::operator != (PEMatrix &mat)
{
    return !((*this) == mat);
}


PEMatrix PEMatrix::complement(int row, int col)
{
	if(row >= m_col || col >= m_col){
		PELog("there is must be row<max_row && col<max_col");
		return PEMatrix(0, 0);
	}
	PEMatrix retMat(m_row-1, m_col-1);
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
			retMat.Elm(i1, j1) = m_data[ID(i0, j0)];
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
			PEMatrix mat = this->complement(0, i);
			sum = i%2==0 ? sum + Elm(0, i)*mat.morel() : sum - Elm(0, i)*mat.morel();
		}
	}
	return sum;
}

PEMatrix PEMatrix::IdentityMat(int rank)
{
	PEMatrix mat(rank, rank);
	for(int i=0; i<rank; ++i){
		for(int j=0; j<rank; ++j){
			if(i==j){
				mat.Elm(i, j) = 1.0;
			}else{
				mat.Elm(i, j) = 0.0;
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

PEMatrix PEMatrix::inverse()
{
	PEMatrix mat;
	mat = *this;
	PEMatrix inv = PEMatrix::IdentityMat(m_row);
	for(int i=0; i<m_row; ++i){
		if(mat.Elm(i, i) == 0.0){
			for(int j=i+1; j<m_row; ++j){
				if(mat.Elm(j, i) != 0){
					mat.exchangeRow(i, j);
					inv.exchangeRow(i, j);
					break;
				}
			}
		}
		float f = mat.Elm(i, i);
		for(int j=0; j<m_col; ++j){
			mat.Elm(i, j) = mat.Elm(i, j);
			inv.Elm(i, j) = inv.Elm(i, j)/f;
		}
		for(int r=0; r<m_row; ++r){
			if(r == i){
				continue;
			}
			float a = mat.Elm(r, i)/mat.Elm(i, i);
			for(int k=0; k<m_col; ++k){
				mat.Elm(r, k) = mat.Elm(r, k)-a*mat.Elm(i, k);
				inv.Elm(r, k) = inv.Elm(r, k)-a*inv.Elm(i, k);
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

PEMatrix operator * (PEMatrix &mat, float scale)
{
    PEMatrix result(mat.m_row, mat.m_col);
    for(int i=0; i<mat.m_row; ++i){
        for(int j=0; j<mat.m_col; ++j){
            result.Elm(i, j) = mat.Elm(i, j)*scale;
        }
    }
    return result;
}

PEMatrix operator - (PEMatrix &A, PEMatrix &B)
{
    PEMatrix result(A.m_row, A.m_col);
    for(int i=0; i<result.m_row; ++i){
        if(i>= B.m_row){
            continue;
        }
        for(int j=0; j<result.m_col; ++j){
            if(j < B.m_col){
                result.Elm(i, j) = A.Elm(i, j) - B.Elm(i, j);
            }
        }
    }
    return result;
}

PEMatrix operator + (PEMatrix &A, PEMatrix &B)
{
    PEMatrix result(A.m_row, A.m_col);
    for(int i=0; i<result.m_row; ++i){
        if(i>= B.m_row){
            continue;
        }
        for(int j=0; j<result.m_col; ++j){
            if(j < B.m_col){
                result.Elm(i, j) = A.Elm(i, j) + B.Elm(i, j);
            }
        }
    }
    return result;
}
PEMatrix operator * (PEMatrix &A, PEMatrix &B)
{
    PEMatrix result(A.m_row, A.m_col);
    for(int i=0; i<result.m_row; ++i){
        if(i>= B.m_row){
            continue;
        }
        for(int j=0; j<result.m_col; ++j){
            if(j < B.m_col){
                result.Elm(i, j) = A.Elm(i, j) * B.Elm(i, j);
            }
        }
    }
    return result;
}

PEMatrix operator / (PEMatrix &A, PEMatrix &B)
{
    PEMatrix result(A.m_row, A.m_col);
    for(int i=0; i<result.m_row; ++i){
        if(i>= B.m_row){
            continue;
        }
        for(int j=0; j<result.m_col; ++j){
            if(j < B.m_col){
                result.Elm(i, j) = A.Elm(i, j) / B.Elm(i, j);
            }
        }
    }
    return result;
}

PEMatrix cross(PEMatrix &A, PEMatrix &B)
{
	if(A.m_col != B.m_row){
		return PEMatrix(0, 0);
	}
	PEMatrix result(A.m_row, B.m_col);
	for(int i=0; i<A.m_row; ++i){
		for(int j=0; j<B.m_col; ++j){
            float tmp = 0.0;
			for(int k=0; k<A.m_col; ++k){
				tmp += A.Elm(i, k)*B.Elm(k, j);
			}
            result.Elm(i, j) = tmp;
		}
	}
    return result;
}

float *PEMatrix::getData()
{
    return m_data;
}


PEMatrix PEMatrix::RotationMatrix(V3D axis, float angle)
{
    PEMatrix mat(4, 4);
    float sa = sin(angle/180.0*M_PI);
    float ca = cos(angle/180.0*M_PI);
    float nx = axis.x;
    float ny = axis.y;
    float nz = axis.z;
    mat.Elm(0, 0) = nx*nx*(1-ca)+ca;
    mat.Elm(0, 1) = nx*ny*(1-ca)+nz*sa;
    mat.Elm(0, 2) = nx*nz*(1-ca)-ny*sa;
    mat.Elm(0, 3) = 0.0;
    
    mat.Elm(1, 0) = ny*nx*(1-ca)-nz*sa;
    mat.Elm(1, 1) = ny*ny*(1-ca)+ca;
    mat.Elm(1, 2) = ny*nz*(1-ca)+nx*sa;
    mat.Elm(1, 3) = 0.0;
    
    mat.Elm(2, 0) = nz*nx*(1-ca)+ny*sa;
    mat.Elm(2, 1) = nz*ny*(1-ca)-nx*sa;
    mat.Elm(2, 2) = nz*nz*(1-ca)+ca;
    mat.Elm(2, 3) = 0.0;
    
    mat.Elm(3, 0) = 0.0;
    mat.Elm(3, 1) = 0.0;
    mat.Elm(3, 2) = 0.0;
    mat.Elm(3, 3) = 1.0;
    
    return mat;
}

