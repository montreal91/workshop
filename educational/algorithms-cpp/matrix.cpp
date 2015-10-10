#include "matrix.h"

Matrix::Matrix( int rows, int columns)
{
    row = rows;
    col = columns;
    M = vector2D(rows, vectorD(columns));
}

Matrix::Matrix( int n )
{
    row = n;
    col = n;
    M = vector2D(n, vectorD(n));
}

Matrix::Matrix(int n, double d)
{
    row = n;
    col = n;
    M = vector2D(n, vectorD(n));
    for (int i = 0; i < n; i++)
        M[i][i] = d;
}

Matrix::Matrix(const vector<double>&D)
{
    row = D.size();
    col = D.size();
    M = vector2D(row, vectorD(col));
    for (int i = 0; i < D.size(); i++)
        M[i][i] = D[i];
}

Matrix::Matrix(vector2D &V)
{
    row = V.size();
    col = V[0].size();
    M = V;
}

int Matrix::getR()
{
    return row;
}

int Matrix::getC()
{
    return col;
}

void Matrix::rand(int mod)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            M[i][j] = std::rand() % mod;
        }
    }
}

void Matrix::print(ostream &out)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            out << M[i][j] << "\t";
        }
        out << endl;
    }
}


vectorD &Matrix::operator[](int R)
{
    return M[R];
}

// ostream &operator << (ostream &os, Matrix &A)
// {
//     for (int i = 0; i < A.row; i++){
//         for (int j = 0; j < A.col; j++){
//             os << (A[i][j]) << "\t";
//         }
//         os << endl;
//     }
//     return os;
// }

Matrix Matrix::operator+(Matrix &B){
    Matrix C(row, col);
    if ((row == B.row) && (col == B.col))
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                C[i][j] = M[i][j] + B[i][j];
        }
    return C;
}

Matrix Matrix::operator-(Matrix &B)
{
    Matrix C(row, col);
    if ((row == B.row) && (col == B.col))
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                C[i][j] = M[i][j] - B[i][j];
        }
    return C;
}

Matrix Matrix::operator*(Matrix &B)
{
    Matrix C(row, B.col);
    if (col == B.row)
        for (int i = 0; i < row; i++)
            for (int j = 0; j < B.col; j++)
            {
                C[i][j] = 0;
                for (int k = 0; k < col; k++)
                    C[i][j] += M[i][k] * B[k][j];
            }
    return C;
}

Matrix
Matrix::Transpanate() {
    Matrix res( this->col, this->row );
    for( int i=0; i < this->row; i++ ){
        for( int j=0; j < this->col; j++ ) {
            res[j][i] = this->M[i][j];
        }
    }
    return res;
}

void
Matrix::PrintMatrix() const {
    for( int i=0; i<this->row; i++ ) {
        for( int j=0; j<this->col; j++ ) {
            std::cout << this->M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Matrix
// Matrix::InverseMatrix() {
//     Matrix res( this->row );
//     Matrix temp = *this;

//     if ( this->row == this->col ) {
//         for( int i=0; i<this->row; i++ ) {
//             double d = T[i][j];
//         }
//     }
// }