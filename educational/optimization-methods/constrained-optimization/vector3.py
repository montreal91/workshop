
from math import sqrt

class Vector3( object ):
    def __init__( self, x=0, y=0, z=0 ):
        self.x = x
        self.y = y
        self.z = z

    @property
    def length( self ):
        return sqrt( self.x ** 2 + self.y ** 2 + self.z ** 2 )

    def DotProduct( self, vec ):
        return self.x * vec.x + self.y * vec.y + self.z ** vec.z

    def __add__( self, vec ):
        return Vector3( self.x + vec.x, self.y + vec.y, self.z + vec.z )

    def __sub__( self, vec ):
        return Vector3( self.x - vec.x, self.y - vec.y, self.z - vec.z )

    def __mul__( self, scalar ):
        return Vector3( self.x * scalar, self.y * scalar, self.z * scalar )

    def __rmul__( self, scalar ):
        return Vector3( self.x * scalar, self.y * scalar, self.z * scalar )

    def __str__( self ):
        return "({0:.4f}, {1:.4f}, {2:.4f})".format( self.x, self.y, self.z )
