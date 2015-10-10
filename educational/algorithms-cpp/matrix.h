#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<double> vectorD;
typedef vector<vectorD> vector2D;

class Matrix{
    vector2D M;
    int col, row;
public:
    Matrix(int rows, int columns);
    Matrix(int n);
    Matrix(int n, double d);
    Matrix(const vectorD &D);
    Matrix(vector2D &V);
    int getR();
    int getC();
    void rand(int mod);
    void print(ostream &out = cout);
    // friend ostream &operator << (ostream &os, Matrix &A);
    vectorD &operator[](int R);
    Matrix operator+(Matrix &B);
    Matrix operator-(Matrix &B);
    Matrix operator*(Matrix &B);
    Matrix Transpanate();
    // Matrix InverseMatrix();
    void PrintMatrix() const;
    ~Matrix(){
        std::cout << "destroy vectors!\n";
    };
};
