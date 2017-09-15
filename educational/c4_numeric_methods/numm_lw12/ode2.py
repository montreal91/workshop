
import numpy as np
import json

from math import pi, sqrt

def SolveOde2( a=0, b=0, N=0, alpha0=0, alpha1=0, beta0=0, beta1=0, gamma0=0, gamma1=0, A=0, B=0, C=0 ):
    assert b > a

    column_b = []
    step = ( b - a ) / N
    matrix_a = np.array( [0.0] * ( N + 1 ) ) # @UndefinedVariable
    matrix_a[0] = 2 * step * alpha0 - 3 * beta0
    matrix_a[1] = 4 * beta0
    matrix_a[2] = -beta0
    column_b.append( 2 * step * gamma0 )

    row1 = np.array( [0.0] * ( N + 1 ) ) # @UndefinedVariable
    row1[N - 2] = beta1
    row1[N - 1] = -4 * beta1
    row1[N] = 2 * step * alpha1 + 3 * beta1
    matrix_a = np.vstack( [matrix_a, row1] ) # @UndefinedVariable
    column_b.append( 2 * step * gamma1 )

    for i in range( 1, N ):
        row = np.array( [0.0] * ( N + 1 ) ) # @UndefinedVariable
        row[i - 1] = 2 * A + B * step
        row[i] = -4 * A + 2 * C * step ** 2
        row[i + 1] = 2 * A - B * step
        matrix_a = np.vstack( [matrix_a, row] ) # @UndefinedVariable
        column_b.append( 0 )
    res = {}
    res["xses"] = [a + step * i for i in range( N + 1 )]
    res["vals"] = list( np.linalg.solve( matrix_a, column_b ) ) # @UndefinedVariable
    with open( "numm_lw12/out.json", "w" ) as fl:
        fl.write( "out=[" + json.dumps( res ) + "]" )

if __name__ == "__main__":
    SolveOde2( 
        a=0,
        b=pi / 4,
        N=100,
        alpha0=1,
        alpha1=1,
        beta0=-1,
        beta1=0,
        gamma0=-3 * sqrt( 2 ),
        gamma1=1,
        A=1,
        B=0,
        C=9
    )
    print( "Done" )
