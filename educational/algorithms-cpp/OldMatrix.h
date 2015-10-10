#pragma once
#include <iostream>
#include <cstdlib>


using namespace std;

class OldMatrix
{
private:
    double **M;
    int Row, Col;
public:
    OldMatrix(int rows, int columns);
    OldMatrix(int n);
    OldMatrix(int n, double d);
    OldMatrix(int n, double *d);
    OldMatrix(int n, int m, double **A);
    int GetR();
    int GetC();
    double* operator [] (int R);
    void rand(int mod);
    // friend ostream& operator << (ostream& os, OldMatrix&A); //??Ïî÷åìó ôðåíäîâñêàÿ?// Âåäü ýòî äîëæíî áûòü ìòåîäîì êàóòà, à íå íàøåé ìàòðèöû?
    OldMatrix operator + (OldMatrix &B);
    OldMatrix operator - (OldMatrix &B);
    OldMatrix operator * (OldMatrix &B);
    ~OldMatrix();
};

