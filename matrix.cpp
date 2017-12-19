#include <iostream>
#include <fstream>
#include <iomanip>

#include "matrix.h"

CMatrix::CMatrix(int h, int w, double v, double f)
{
    if(h <= 0 || w <= 0)
    {
        throw WrongDim();
    }
    try
    {
        this->array = new CArray(h, w, v, f);
    }catch(...)
    {
        throw bad_alloc();
    }
}

CMatrix::CMatrix(const CMatrix& m)
{
    m.array->n++;
    this->array = m.array;
}

CMatrix::CMatrix(std::fstream &f)
{
    array = new CArray(f);
}

CMatrix::CMatrix()
{
    array = new CArray();
}

CMatrix::~CMatrix()
{
    if(--array->n==0)
        delete array;
}

void CMatrix::check(int i, int j)
{
    if(i < 0 || i >= array->m_row || j < 0 || j >= array->m_col)
        throw WrongDim();
}

int CMatrix::getRows() const
{
    return this->array->m_row;
}

int CMatrix::getColumns() const
{
    return this->array->m_col;
}

double CMatrix::read(int col, int row) const
{
    return this->array->A[col][row];
}

void CMatrix::write(int col, int row, double val)
{
    array = array->detach();
    this->array->A[col][row] = val;
}


std::ostream& operator<<(std::ostream &os, CMatrix &matrix)
{
    for (int i = 0; i < matrix.array->m_row; i++)
    {
        os << "[ ";
        for (int j = 0; j < matrix.array->m_col; j++)
        {
            os << std::fixed << std::setprecision(1) << matrix.array->A[i][j] << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

CMatrix CMatrix::operator=(CMatrix mat)
{
    mat.array->n++;
    if(--array->n == 0)
        delete array;

    array = mat.array;
    return *this;
}
/*
CMatrix CMatrix::operator=(double num)
{
    /*if(array->n > 1)
    {
        CArray *arr = new CArray(1, 1, num);
        this->array->n--;
        this->array = arr;
        return *this;
    }*/
    if(array->n==1)
    {
        array->A
    }

    //
}*/

CMatrix CMatrix::operator*(CMatrix mat)
{
    if(mat.array == NULL)
        throw null_as_argument();
    if(this->getColumns() != mat.getRows())
        throw WrongDim();

    CMatrix newMat(this->getRows(), mat.getColumns());

    for(int i = 0; i < newMat.getRows(); i++)
    {
        for(int j = 0; j < newMat.getColumns(); j++)
        {
            double tmp = 0.0f;

            for(int k = 0; k < this->getColumns(); k++)
            {
                tmp += read(i,k) * mat.read(k,j);
            }

            newMat.write(i,j,tmp);
        }
    }

    return newMat;
}
/*
double* CMatrix::operator[](int i)
{
    check(i, getRows());
    array = array->detach();
    return array->A[i];
    //return CMatrix(*this);
}
*/

CMatrix::Cref CMatrix::operator[](int i)
{
    check(i, getRows());
    //return array->A[i];
    return Cref(*this,i);
}

CMatrix::Cref::Cref(CMatrix& matrix, int col): mat(matrix), m_col(col)
{

}

CMatrix::Cref::operator double()
{
    return mat.read(m_col, m_row);
}

CMatrix::Cref& CMatrix::Cref::operator=(double num)
{
    mat.write(m_col, m_row, num);
    return *this;
}

CMatrix::Cref& CMatrix::Cref::operator=(Cref& ref)
{
    return operator=((double)ref);
}

double* CMatrix::Cref::operator[](int i)
{
    mat.check(i, mat.getRows());
    return mat.array->A[i];
}
