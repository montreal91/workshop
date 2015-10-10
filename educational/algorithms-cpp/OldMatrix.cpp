#include "OldMatrix.h"


OldMatrix::OldMatrix(int rows, int columns)
{
    Row = rows;
    Col = columns;
    M = new double *[Row];
    for (int i = 0; i < Row; i++)
        M[i] = new double[Col];
}

OldMatrix::OldMatrix(int n)
{
    Row = n;
    Col = n;
    M = new double *[Row];
    for (int i = 0; i < Row; i++)
        M[i] = new double[Col];
}

OldMatrix::OldMatrix(int n, double d)
{
    Row = n;
    Col = n;
    M = new double *[Row];
    for (int i = 0; i < Row; i++)
    {
        M[i] = new double[Col];
        M[i][i] = d;
    }

}

OldMatrix::OldMatrix(int n, double *d)
{
    Row = n;
    Col = n;
    M = new double *[Row];
    for (int i = 0; i < Row; i++)
    {
        M[i] = new double[Col];
        M[i][i] = d[i];
    }
}

OldMatrix::OldMatrix(int n, int m, double **A)
{
    Row = n;
    Col = m;
    M = new double *[Row];
    for (int i = 0; i < Row; i++)
    {
        M[i] = new double[Col];
        for (int j = 0; j < Col; j++)
            M[i][j] = A[i][j];
    }
}
/*
OldMatrix::OldMatrix(OldMatrix &B)
{
    Col = B->Col;
    Row = B.Row;
    M = new double *[Row];
    for (int i = 0; i < Row; i++)
    {
        M[i] = new double[Col];
        for (int j = 0; j < Col; j++)
            M[i][j] = B[i][j];
    }
}
*/
int OldMatrix::GetR()
{
    return Row;
}

int OldMatrix::GetC()
{
    return Col;
}

double* OldMatrix::operator [] (int R)
{
    return M[R];
}

void OldMatrix::rand(int mod)
{
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            M[i][j] = std::rand() % mod;
}

// ostream& operator << (ostream& os, OldMatrix &A)
// {
//     for (int i = 0; i < A.Row; i++){
//         for (int j = 0; j < A.Col; j++){
//             os << (A[i][j]) << "\t";
//         }
//         os << endl;
//     }
//     return os;
// }

OldMatrix OldMatrix::operator+ (OldMatrix* B)
{
    OldMatrix C(Row, Col);
    if ((Row == B->Row) && (Col == B->Col))
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++)
                C[i][j] = M[i][j] + B[i][j];
        }
    return C;
}

OldMatrix OldMatrix::operator - (OldMatrix &B)
{
    OldMatrix C(Row, Col);
    if ((Row == B.Row) && (Col == B.Col))
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++)
                C[i][j] = M[i][j] - B[i][j];
        }
    return C;
}

OldMatrix OldMatrix::operator * (OldMatrix* B)
{
    OldMatrix C(Row, B->Col);
    if (Col == B->Row)
        for (int i = 0; i < Row; i++)
            for (int j = 0; j < B->Col; j++)
            {
                C[i][j] = 0;
                for (int k = 0; k < Col; k++)
                    C[i][j] += M[i][k] * B[k][j];
            }
    return C;
}

OldMatrix::~OldMatrix()
{
    for (int i = 0; i < Row; i++)
        delete[] M[i];
    delete[] M;
}
