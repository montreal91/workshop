
class OneDMinSeeker( object ):
    def __init__( self, callback, accuracy=0.01 ):
        super( OneDMinSeeker, self ).__init__( )
        self._callback = callback
        self._accuracy = accuracy

    def _IsTripleLucky( self, start, end, middle ):
        start_value     = self._callback( start )
        end_value       = self._callback( end )
        middle_value    = self._callback( middle )

        return middle_value < start_value and middle_value < end_value

    def _IsGrowing( self, start, end, middle ):
        start_value     = self._callback( start )
        middle_value    = self._callback( middle )
        end_value       = self._callback( end )

        return start_value < middle_value < end_value

    def GetLuckyTriple( self ):
        start   = -2
        middle  = -1
        end     = 0
        for i in range( 100 ):
            if self._IsTripleLucky( start, end, middle ):
                return start, middle, end
            elif self._IsGrowing( start, end, middle ):
                break
            start   = middle
            middle  = end
            end     = middle + ( middle - start ) * 2

        start   = 0
        middle  = -1
        end     = -2
        for i in range( 100 ):
            if self._IsTripleLucky( start, end, middle ):
                return start, end, middle
            start   = middle
            middle  = end
            end     = middle + ( middle - start ) * 2
        return None


    def _GetLocalMinimum( self, start, end ):
        found = False
        while not found:
            middle      = ( start + end ) / 2 # c -- середина отрезка
            epsilon     = self._accuracy / 4
            left        = middle - epsilon # yk
            right       = middle + epsilon # zk
            call_left   = self._callback( left ) # f( yk )
            call_right  = self._callback( right ) # f( zk )

            if call_left >= call_right:
                start = left
            elif call_left < call_right:
                end = right

            if abs( start - end ) < self._accuracy:
                found = True
        return ( start + end ) / 2


    def GetMinimum( self ):
        lucky_triple = self.GetLuckyTriple()
        if lucky_triple is not None:
            return self._GetLocalMinimum( lucky_triple[0], lucky_triple[-1] )
        else:
            return None
