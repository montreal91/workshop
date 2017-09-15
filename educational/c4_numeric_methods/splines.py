
import numpy as np

def GetStandardConditionsMatrix( nodes ):
    N = len( nodes )
    A = None
    B = [0] * ( 3 * N - 5 ) # @UndefinedVariable

    for i in range( N - 1 ):
        row = [0] * ( 3 * N - 3 )
        h = nodes[i + 1][0] - nodes[i][0]
        B[i] = nodes[i + 1][1] - nodes[i][1]

        row[i] = h
        row[N - 1 + i] = -0.5 * h ** 2
        row[2 * N - 2 + i] = ( 1 / 6 ) * h ** 3

        if A is not None:
            A = np.vstack( [A, row] ) # @UndefinedVariable
        else:
            A = np.array( row ) # @UndefinedVariable

    for i in range( 1, N - 1 ):
        row = [0] * ( 3 * N - 3 )
        h = nodes[i + 1][0] - nodes[i][0]
        row[i - 1] = 1
        row[i] = -1
        row[N - 1 + i] = h
        row[2 * N - 2 + i] = -0.5 * h ** 2
        A = np.vstack( [A, row] ) # @UndefinedVariable

    for i in range( 1, N - 1 ):
        row = [0] * ( 3 * N - 3 )
        h = nodes[i + 1][0] - nodes[i][0]
        row[N - 2 + i] = 1
        row[N - 1 + i] = -1
        row[2 * N - 2 + i] = h
        A = np.vstack( [A, row] ) # @UndefinedVariable

    return A, B

def AttachAdditionalCondition( matrix_a, column_b, condition_a, condition_b ):
    A = np.vstack( [matrix_a, condition_a] ) # @UndefinedVariable
    B = np.append( column_b, condition_b ) # @UndefinedVariable
    return A, B

def GetSplinesCoefficients( nodes, additional_condions ):
    A, B = GetStandardConditionsMatrix( nodes )
    for row in additional_condions:
        A, B = AttachAdditionalCondition( A, B, row[0], row[1] )

    return np.linalg.solve( A, B ) # @UndefinedVariable

def ApproximateFunctionBySpline( nodes, additional_conditions, x=0 ):
    coefficients = GetSplinesCoefficients( nodes, additional_conditions )
    for i in range( len( nodes ) - 1 ):
        if nodes[i][0] <= x <= nodes[i + 1][0]:
            xi = nodes[i][0]
            b = coefficients[i]
            c = coefficients[i + len( nodes ) - 1]
            d = coefficients[i + 2 * len( nodes ) - 2]
            return nodes[i][1] + b * ( x - xi ) + ( c / 2 ) * ( x - xi ) ** 2 + ( d / 6 ) * ( x - xi ) ** 3
    return None


if __name__ == "__main__":
    nodes = [
        ( 0.2, 1.2342 ),
        ( 0.24, 1.4532 ),
        ( 0.25, 1.8723 ),
        ( 0.28, 2.1234 ),
        ( 0.35, 2.3421 ),
        ( 0.38, 2.4321 ),
    ]
    additional_conditions = [
        ( [0, 0, 0, 0, 0, 3, 0, 0, 0, 0, -0.01, 0, 0, 0, 0], 2.2431 ),
        ( [0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0], 3.6231 )
    ]
    print( ApproximateFunctionBySpline( nodes, additional_conditions, x=0.26 ) )

