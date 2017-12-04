#include <iostream>
#include <fstream>

#include "matrix.h"

CMatrix::CMatrix(int h, int w, double v, double f == 0.0f)
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

CMatrix::CMatrix(CMatrix& m)
{
    m.array->n++;
    this->array = m.array;
}

CMatrix::CMatrix(std::fstream &f)
{
    array = new CArray(f)
}

CMatrix::CMatrix()
{
    array = new CArray()
}

CMatrix::~CMatrix()
{
    if(--array->n==0)
        delete array;
}


std::ostream& operator<<(std::ostream &os, CMatrix &matrix)
{
    os << "[";
    for (int i = 0; i < matrix.array->m_row; i++)
    {
        for (int j = 0; j < matrix.array->m_col; j++)
        {
            os << matrix.array->A[i][j] << " ";
        }
        os << std::endl;
    }
    os << "]";
    return os;
}

CMatrix& CMatrix::operator=(double** num)
{
    if(num == nullptr)
    {
        throw null_as_argument;
    }
    if(array->n == 1)
    {
        array->assign(num); //przypisz tablicę jeśli ta nie jest nigdzie indziej wykorzystana
    }
    else
    {
        CArray* sub = CArray(1,1,num);
        this->array->n--;
        this->array = sub;
    }
    return *this;
}

CMatrix& CMatrix::operator=(CMatrix &mat)
{
    mat.array->n++;
    if(--array->n == 0)
        delete array;

    array = mat.array;
    return *this;
}

CMatrix operator*(CMatrix &mat1, CMatrix &mat2)
{
    if(mat1.array == NULL || mat2.array == NULL)
        throw null_as_argument();
    if(mat1.array->m_col != mat2.array->m_row)
        throw WrongDim();

    CMatrix newMat(mat1.array->m_row, mat2.array->m_col);

    for(int i = 0; i < newMat.array->m_col; i++)
    {
        for(int j = 0; j < newMat.array->m_col; i++)
        {
            double tmp = 0.0f;

            for(int k = 0; k < mat1.array->m_col; k++)
            {
                tmp += mat1.array->A[i][k] * mat2.array->A[k][j];
            }

            newMat.array->A[i][j] = tmp;
        }
    }

    return newMat;
}

//double
