
from vector import Vector


def TargetFunc1( vec ):
    return vec.x ** 2 + vec.y ** 2

def TargetFuncDerivative1( vec ):
    return Vector( 2 * vec.x, 2 * vec.y )


def TargetFunc2( vec ):
    return vec.x ** 2 + 10 * vec.y ** 2

def TargetFuncDerivative2( vec ):
    return Vector( 2 * vec.x, 20 * vec.y )

def TargetFunc3( vec ):
    return 100 * ( vec.y - vec.x ** 2 ) ** 2 + ( 1 - vec.x ) ** 2

def TargetFuncDerivative3( vec ):
    brace   = vec.y - vec.x ** 2
    rez     = Vector()
    rez.x   = -400 * vec.x * brace - 2 * ( 1 - vec.x )
    rez.y   = 200 * brace
    return rez
