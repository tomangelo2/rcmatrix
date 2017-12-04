#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

#include "array.h"

class CMatrix
{
public:
    //Konstruktor tworzący nową macierz
    //h - wysokość, w - szerokość, v - wartość na przekątnej, f - wartość pozostałych pól macierzy
    CMatrix(int w, int h, double v = 0.0f, double f = 0.0f);
    //Konstruktor kopiujący macierz
    CMatrix(CMatrix &m);
    //Konstruktor tworzący macierz z wczytanego pliku
    CMatrix(std::fstream &f);
    //Pusty konstruktor
    CMatrix();
    ~CMatrix();

    /*Metody*/


    /*operatory*/
    //Przypisanie macierzy jako klasy
    CMatrix& operator=(CMatrix &mat);
    //Przypisywanie macierzy jako 2-wymiarowej tablicy
    CMatrix& operator=(double **num);
    //Operator przypisujący do wyjścia
    friend std::ostream& operator<<(std::ostream &os, CMatrix &matrix);
    //Mnożenie klasy macierzy
    CMatrix& operator*(CMatrix &mat);
    //Mnożenie tablicy
    //CMatrix& operator*(double **num);
    //Wybór elementu
    double* operator[](int i);


private:
    CArray* array;
};

#endif // MATRIX_H
