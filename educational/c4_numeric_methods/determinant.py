
import numpy as np
from functools import reduce

def GetDeterminant( matrix ):
    pivots = []
    size = len( matrix[0] )
    for i in range( size ):
        pivot = matrix[i, i]
        if pivot != 0:
            pivots.append( pivot )
            matrix[i] /= pivot
            for j in range( i + 1, size ):
                matrix[j] -= matrix[i] * matrix[j, i]
        else:
            # I need to do it fast, so don't be upset with bad code
            for k in range( i + 1, size ):
                if matrix[i, k] != 0:
                    bubble = matrix[i].copy()
                    matrix[i] = matrix[k]
                    matrix[k] = bubble
                    break
            if matrix[i, i] == 0:
                return 0
            pivot = matrix[i, i]
            pivots.append( pivot )
            pivots.append( -1 )
            matrix[i] /= pivot
            for j in range( i + 1, size ):
                matrix[j] -= matrix[i] * matrix[j, i]
    return reduce( lambda x, y: x * y, pivots )


if __name__ == '__main__':
    m = np.array( [1.0, 0.42, 0.54, 0.66, 0.42, 1.00, 0.32, 0.44, 0.54, 0.32, 1.00, 0.22, 0.66, 0.44, 0.22, 1.00] ).reshape( 4, 4 ) # @UndefinedVariable
    print( GetDeterminant( m ) )
