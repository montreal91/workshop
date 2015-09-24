
from decimal import Decimal, getcontext

getcontext().prec = 10

class RMinimumSeeker( object ):
    """docstring for RMinimumSeeker"""
    def __init__( self, callback, accuracy=0.01 ):
        super( RMinimumSeeker, self ).__init__()
        self._callback = callback
        self._accuracy = Decimal( str( accuracy ) )

    def _IsTripleLucky( self, start, end, middle ):
        start_value     = self._callback( start )
        end_value       = self._callback( end )
        middle_value    = self._callback( middle )

        return middle_value < start_value and middle_value < end_value

    def _GetLuckyTriple( self ):
        middle = Decimal("-125000")
        for i in range( 1000 ):
            start   = middle
            end     = start + i
            middle  = ( start + end ) / 2

            if self._IsTripleLucky( start, end, middle ):
                return start, middle, end
        return None

    def _MoveStartCondition( self, start, end ):
        return call_left > call_right

    def _GetLocalMinimum( self, start, end ):
        while True:
            middle = ( start + end ) / 2
            delta = abs( start - end ) / 10
            left = middle - delta
            right = middle + delta
            call_left = self._callback( left )
            call_right = self._callback( right )
            if call_left > call_right:
                start = left
            elif call_left < call_right:
                end = right

            print( start, end, left, right, call_left, call_right )
            if abs( left - right ) < self._accuracy:
                return left


    def GetMinimum( self ):
        lucky_triple = self._GetLuckyTriple()
        if lucky_triple is not None:
            return self._GetLocalMinimum( lucky_triple[ 0 ], lucky_triple[ -1 ] )
        else:
            return None


def TestFunction1( arg ):
    return arg ** 2

def TestFunction2( arg ):
    return ( arg - 2000 ) ** 2

def TestFunction3( arg ):
    return 0

def TestFunction4( arg ):
    return abs( arg )

if __name__ == '__main__':
    ms1 = RMinimumSeeker( TestFunction1, accuracy=0.02 )
    res1 = ms1.GetMinimum()
    ms2 = RMinimumSeeker( TestFunction2, accuracy=0.02 )
    # res2 = ms2.GetMinimum()
    ms3 = RMinimumSeeker( TestFunction3 )
    # res3 = ms3.GetMinimum()
    ms4 = RMinimumSeeker( TestFunction4, accuracy=0.02 )
    # res4 = ms4.GetMinimum()
    # print( res1 )
    # print( res2 )
    # print( res3 )
    # print( res4 )

