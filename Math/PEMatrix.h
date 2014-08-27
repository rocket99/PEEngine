#ifndef __PEMatrix_H__
#define __PEMatrix_H__

#include "PEPrefix.h"
#include "PEDataType.h"

class PEMatrix
{
public:
    PEMatrix():m_row(0), m_col(0), m_data(NULL){};
    PEMatrix(int row, int col);
    ~PEMatrix();
    
    PEMatrix(const PEMatrix &mat);
    
    float &Elm(int row, int col);
    float Elm(int row, int col) const;
    void display();
    void displayRow(int row);
    void displayColumn(int col);

    PEMatrix &operator = (const PEMatrix &mat);
    virtual PEMatrix & operator += (const PEMatrix &mat);
    virtual PEMatrix & operator -= (const PEMatrix &mat);
    virtual PEMatrix & operator *= (const PEMatrix &mat);
    virtual PEMatrix & operator /= (const PEMatrix &mat);
    virtual bool operator == (const PEMatrix &mat);
    virtual bool operator != (const PEMatrix &mat);
    
    friend PEMatrix operator * (const PEMatrix &mat, float scale);
    friend PEMatrix operator - (const PEMatrix &A, const PEMatrix &B);
    friend PEMatrix operator * (const PEMatrix &A, const PEMatrix &B);
    friend PEMatrix operator / (const PEMatrix &A, const PEMatrix &B);
    friend PEMatrix operator + (const PEMatrix &A, const PEMatrix &B);
    friend PEMatrix cross(const PEMatrix &A, const PEMatrix &B);

    int getRowNum();
    int getColumnNum();

    int getRowNum() const;
    int getColumnNum() const;
    
    PEMatrix complement(int row, int col);//algebra complement
    float morel();
		
    static PEMatrix IdentityMat(int rank);

    void exchangeRow(int row0, int row2);
    void exchangeColumn(int col0, int col1);
    PEMatrix inverse();

    void transfers();

    float *getData();
    
    
    static PEMatrix RotationMatrix(V3D axis, float angle);
protected:
    int m_col, m_row;
    float *m_data;

    int ID(int row, int col);
    int ID(int row, int col) const;
private:
};

#endif

