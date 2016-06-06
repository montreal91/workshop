

class PPlayer( object ):
    def __init__( self ):
        super( PPlayer, self ).__init__()
        self._stack     = 1000
        self._active    = True
        self._made_move = False
        self._stake     = 0


    @property
    def stack( self ):
        return self._stack


    @property
    def active( self ):
        return self._active


    @property
    def made_move(self):
        return self._made_move


    @property
    def stake( self ):
        return self._stake


    def MakeStake( self, stake ):
        self._made_move = True
        if self._stack >= stake:
            self._stack -= stake
            self._stake += stake
            return stake
        else:
            stack = self._stack
            self._stack = 0
            self._stake += stack
            return stack


    def SayFold( self ):
        self._made_move = True
        self._active = False

    def SayCheck( self ):
        self._made_move = True
