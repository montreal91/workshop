
import math

class Vector(object):
    def __init__(self, x=0, y=0):
        super(Vector, self).__init__()
        self.x = x
        self.y = y

def GetVectorLengtn(vec=Vector(0,0)):
    underroot = vec.x ** 2 + vec.y ** 2
    return math.sqrt(underroot)

def GetNormalizedVector(vec=Vector(0,0)):
    length = GetVectorLengtn(vec=vec)
    return Vector(x=vec.x / length, y=vec.y / length)

def GetRotatedVector(vec=Vector(0,0), angle=0):
    res = Vector()
    res.x = vec.x * math.cos(angle) - vec.y * math.sin(angle)
    res.y = vec.x * math.sin(angle) + vec.y * math.cos(angle)
    return res

def GetRotatedVectorAroundOrigin(vec=Vector(0,0), origin=Vector(0,0), angle=0):
    vec1 = Vector()
    vec1.x = vec.x - origin.x
    vec1.y = vec.y - origin.y

    rotated_vec1 = GetRotatedVector(vec=vec1, angle=angle)

    res = Vector()
    res.x = rotated_vec1.x + origin.x
    res.y = rotated_vec1.y + origin.y

    return res



if __name__ == '__main__':
    vec = Vector(3, 4)
    res = GetRotatedVector(vec, math.pi/2)
    print( res.x, res.y )

    vec2 = Vector(8, 9)
    origin = Vector(5, 5)
    res = GetRotatedVectorAroundOrigin(vec2, origin, math.pi / 2)
    print( res.x, res.y )
