
import math

class DPoint( object ):
    def __init__( self, x=0, y=0 ):
        self._x = x
        self._y = y

    @property
    def x( self ):
        return self._x

    @property
    def y( self ):
        return self._y

def GetParabolaVertex( a, b, c ):
    det_abc = b.x*b.x*c.x - b.x*c.x*c.x - a.x*a.x*c.x + a.x*c.x*c.x + a.x*a.x*b.x - a.x*b.x*b.x
    det_x1 = b.y*c.x - b.x*c.y - a.y*c.x + a.x*c.y + a.y*b.x - a.x*b.y
    det_x2 = b.x*b.x*c.y - b.y*c.x*c.x - a.x*a.x*c.y + a.y*c.x*c.x + a.x*a.x*b.y - a.y*b.x*b.x
    coef_a = det_x1 / det_abc
    coef_b = det_x2 / det_abc
    return - coef_b / (2 * coef_a)

def GetMinimumOfThree( a, b, c ):
    if a <= b and a <= c:
        return a
    elif b <= a and b <= c:
        return b
    elif c <= a and c <= b:
        return c

def FindMinParabolicMethod( start, callback, step=0.01, eps1=0.01, eps2=0.02 ):
    to_stop = False
    current_x = start
    vertex, counter = 0, 0
    while not to_stop:
        # print(counter, current_x)
        point1 = DPoint( x=current_x, y=callback( current_x ) )
        next_x = current_x + step
        point2 = DPoint( x=next_x, y=callback( next_x ) )
        if point1.y > point2.y:
            last_x = current_x + step * 2
        else:
            last_x = current_x - step

        point3 = DPoint( x=last_x, y=callback( last_x ) )
        call_min = GetMinimumOfThree( point1.y, point2.y, point3.y )
        try:
            vertex = GetParabolaVertex( point1, point2, point3 )
        except ZeroDivisionError:
            vertex = GetMinimumOfThree( current_x, next_x, last_x )
        call_v = callback( vertex )

        condition_one = abs( ( call_min - call_v ) / call_v ) < eps1
        condition_two = abs( ( GetMinimumOfThree( current_x, next_x, last_x ) - vertex) / vertex ) < eps2
        if condition_one and condition_two:
            to_stop = True
        else:
            current_x = vertex
            counter += 1
    return vertex

def TargetFunction1(arg):
    return abs(arg)+ 7

def TargetFunction2(arg):
    return arg ** 2 - 4 * arg - 5

def TargetFunction3(arg):
    return (arg - 1) * (arg - 2) * (arg - 3) * (arg - 4)

def TargetFunction4(arg):
    return math.sin(arg) + arg * arg

def TargetFunction5(arg):
    return (math.sin(arg) ** 2) * (arg ** 2)

def TargetFunction6(arg):
    return math.exp(arg*arg) + arg * arg

if __name__ == '__main__':
    print(FindMinParabolicMethod(8, TargetFunction4, step=0.001, eps1=0.01, eps2=0.01))
    print(FindMinParabolicMethod(4, TargetFunction5, step=0.001, eps1=0.0025, eps2=0.0025))
    print(FindMinParabolicMethod(10, TargetFunction6, step=0.01, eps1=0.04, eps2=0.04))
