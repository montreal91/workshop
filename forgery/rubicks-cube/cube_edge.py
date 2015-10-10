
class RcEdge( object ):
    """docstring for RcEdge"""
    def __init__( self, pieces ):
        super( RcEdge, self ).__init__()
        self._pieces = pieces


    @property
    def left( self ):
        return self._pieces[ 0 ], self._pieces[ 2 ]


    @left.setter
    def left( self, top, bottom ):
        self._pieces[ 0 ] = top
        self._pieces[ 2 ] = bottom


    @property
    def right( self ):
        return self._pieces[ 1 ], self._pieces[ 3 ]


    @right.setter
    def right( self, top, bottom ):
        self._pieces[ 1 ] = top
        self._pieces[ 3 ] = bottom


    @property
    def top( self ):
        return self._pieces[ 0 ], self._pieces[ 1 ]


    @top.setter
    def top( self, left, right ):
        self._pieces[ 0 ] = left
        self._pieces[ 1 ] = right


    @property
    def bottom( self ):
        return self._pieces[ 2 ], self._pieces[ 3 ]


    @bottom.setter
    def bottom( self, left, right ):
        self._pieces[ 2 ] = left
        self._pieces[ 3 ] = right

    
    @property
    def all(self):
        return tuple( self._pieces )
    

    def RotateClockwise( self ):
        old_pieces          = self.all

        self._pieces[ 0 ]   = old_pieces[ 2 ]
        self._pieces[ 1 ]   = old_pieces[ 0 ]
        self._pieces[ 2 ]   = old_pieces[ 3 ]
        self._pieces[ 3 ]   = old_pieces[ 1 ]


    def RotateCounterClockwise( self ):
        old_pieces          = self.all

        self._pieces[ 0 ]   = old_pieces[ 1 ]
        self._pieces[ 1 ]   = old_pieces[ 3 ]
        self._pieces[ 2 ]   = old_pieces[ 0 ]
        self._pieces[ 3 ]   = old_pieces[ 2 ]
