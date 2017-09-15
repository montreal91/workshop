
import math
def CalculateIntegral( a, b, steps, function ):
    assert a < b
    delta = ( b - a ) / steps
    nodes = [a + delta * i for i in range( steps + 1 )]
    values = [( delta * ( function( nodes[i] ) + func( nodes[i + 1] ) ) ) / 2 for i in range( steps )]
    return sum( values )

def func( x ):
    return math.log10( x )

if __name__ == "__main__":
    x = CalculateIntegral( 1.4, 3, 40, func )
    print( x )
