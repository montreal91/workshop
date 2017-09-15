
import math
import numpy as np

def GetMatrixNorm( matrix ):
    sums = [sum( abs( matrix_row ) ) for matrix_row in matrix]
    return max( sums )

def GetEuclidicNorm( vector ):
    squares = [l ** 2 for l in vector]
    return math.sqrt( sum( squares ) )

# Works badly with incorrect inputs
# Why method brakes when matrix is symmetric with big values?
def SolveLinearEquationsSystem( a_matrix, b_column, precision, tau ):
    current_x = b_column.copy()
    while GetEuclidicNorm( a_matrix.dot( current_x ) - b_column ) > precision:
        current_x = tau * b_column - tau * a_matrix.dot( current_x ) + current_x

    return current_x




if __name__ == "__main__":
    m = np.array( # @UndefinedVariable
        [
            [3.4, 1.1, 0.2, -1.2],
            [-0.7, 3.3, -0.3, 0.2],
            [0.4, 0.3, 2.6, 0.2],
            [-0.2, 0.6, 0.4, 1.7]
        ]
    )
    n = np.array( [2, 1.9, -0.4, -6.5] ) # @UndefinedVariable

    print( SolveLinearEquationsSystem( m, n, 0.001, 1 / 80 ) )
