#ifndef __PEMatrix_H__
#define __PEMatrix_H__

#include "PEPrefix.h"

class PEMatrix
{
public:
    PEMatrix():m_row(0), m_col(0),m_data(NULL){};
    PEMatrix(int row, int col);
    ~PEMatrix();

    float &Elm(int row, int col);

    void display();
    void displayRow(int row);
    void displayColumn(int col);

    virtual void operator = (PEMatrix &mat);
    virtual void operator += (PEMatrix &mat);
    virtual void operator -= (PEMatrix &mat);
    virtual void operator *= (PEMatrix &mat);
    virtual void operator /= (PEMatrix &mat);
    virtual bool operator == (PEMatrix &mat);
    virtual bool operator != (PEMatrix &mat);
    
    friend PEMatrix operator * (PEMatrix &mat, float scale);
    friend PEMatrix operator - (PEMatrix &A, PEMatrix &B);
    friend PEMatrix operator * (PEMatrix &A, PEMatrix &B);
    friend PEMatrix operator / (PEMatrix &A, PEMatrix &B);
    friend PEMatrix operator + (PEMatrix &A, PEMatrix &B);
    friend PEMatrix cross(PEMatrix &A, PEMatrix &B);

    int getRowNum();
    int getColumnNum();

    PEMatrix complement(int row, int col);//algebra complement
    float morel();
		
    static PEMatrix IdentityMat(int rank);

    void exchangeRow(int row0, int row2);
    void exchangeColumn(int col0, int col1);
    PEMatrix inverse();

    void transfers();

    float *getData();
	protected:
		int m_col, m_row;
	private:
		float *m_data;
		int ID(int row, int col);
		
};


#endif

