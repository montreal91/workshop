
from functools import reduce

def GetAk( nodes, k ):
    a_denomi = [nodes[k][0] - nodes[i][0] for i in range( len( nodes ) ) if i != k]
    return 1 / reduce( lambda x, y: x * y, a_denomi )

def InterpolateByLagrange( nodes, x ):
    N = len( nodes )
    nomi = [( GetAk( nodes, k ) * nodes[k][1] ) / ( x - nodes[k][0] ) for k in range( N )]
    denomi = [GetAk( nodes, k ) / ( x - nodes[k][0] ) for k in range( N )]
    return sum( nomi ) / sum( denomi )

if __name__ == "__main__":
    nodes = [
        ( 93.0, 11.38 ),
        ( 96.2, 12.80 ),
        ( 100.0, 14.7 ),
        ( 104.2, 17.07 ),
        ( 108.7, 19.91 )
    ]
    print( InterpolateByLagrange( nodes, 93.001 ) )
