
from math import sqrt

class Vector2( object ):
    def __init__( self, x=0, y=0 ):
        self.x = x
        self.y = y

    @property
    def length( self ):
        return sqrt( self.x ** 2 + self.y ** 2 )

    def DotProduct( self, vec ):
        return self.x * vec.x + self.y * vec.y

    def __add__( self, vec ):
        return Vector2( self.x + vec.x, self.y + vec.y )

    def __sub__( self, vec ):
        return Vector2( self.x - vec.x, self.y - vec.y )

    def __mul__( self, scalar ):
        return Vector2( self.x * scalar, self.y * scalar )

    def __rmul__( self, scalar ):
        return Vector2( self.x * scalar, self.y * scalar )

    def __str__( self ):
        return "({0:.4f}, {1:.4f})".format( self.x, self.y )
