#include "matrix.h"

void TestVectorMatrix() {
    Matrix mat1( 3 );
    Matrix mat2( 3, 1 );

    mat1.rand(5);
    mat2.rand(5);

    mat1.PrintMatrix();
    mat2.PrintMatrix();

    Matrix mat3 = mat1 * mat2;
    mat3.PrintMatrix();
}

int main(int argc, char const *argv[])
{
    TestVectorMatrix();

    return 0;
}