
from math import sqrt

class Vector( object ):
    def __init__( self, x=0, y=0 ):
        self.x = x
        self.y = y

    @property
    def length( self ):
        return sqrt( self.x ** 2 + self.y ** 2 )

    def DotProduct( self, vec ):
        return self.x * vec.x + self.y * vec.y

    def __add__( self, vec ):
        return Vector( self.x + vec.x, self.y + vec.y )

    def __sub__( self, vec ):
        return Vector( self.x - vec.x, self.y - vec.y )

    def __mul__( self, scal ):
        return Vector( self.x * scal, self.y * scal )

    def __rmul__( self, scal ):
        return Vector( self.x * scal, self.y * scal )

    def __str__( self ):
        return "({0:f}, {1:f})".format( self.x, self.y )


def TargetFunc( vec ):
    return 4 * vec.x ** 2 + 3 * vec.y ** 2


def TargetFuncDerivative( vec ):
    return Vector( 8 * vec.x, 6 * vec.y )


def GetBeta( vec1, vec0, callback ):
    one = callback( vec1 )
    two = callback( vec0 )
    return one.DotProduct( one - two ) / ( two.length ** 2 )


def FunctionPhi( old_x, antigradient, callback ):
    def SomeInnerFun( alpha ):
        new_vec = Vector( old_x.x + alpha * antigradient.x, old_x.y + alpha * antigradient.y )
        return callback( new_vec )
    return SomeInnerFun


if __name__ == '__main__':
    x0 = Vector( 2, 2 )
    d0 = Vector( -16, -12 )
    x1 = Vector( 0.08, 0.22 )
    caller = FunctionPhi( x0, d0, TargetFunc )
    print( caller( -1 ), caller( 0 ), caller( 2 ) )
    print( caller( 0.137 ) )
    print( "Phi(0):", caller( 0 ) )
    print( "df(x0):", TargetFuncDerivative( x0 ) )
    print( "df(x1):", TargetFuncDerivative( x1 ) )
    print( "Beta  :", GetBeta( x1, x0, TargetFuncDerivative ) )
    print( x0 * 2 )
    print( 2 * x0 )
