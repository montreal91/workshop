
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
        return "({0:.6f}, {1:.6f})".format( self.x, self.y )
