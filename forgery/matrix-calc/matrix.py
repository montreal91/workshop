
from random import randint, random, seed

class Matrix( object ):
    def __init__( self, rows=0, cols=0 ):
        super( Matrix, self ).__init__()
        self._matrix = []
        for i in range( rows ):
            self._matrix.append( [] )
            for j in range( cols ):
                self._matrix[i].append( 0 )

    @property
    def rows(self):
        return len( self._matrix )

    @property
    def cols(self):
        return len( self._matrix[ 0 ] )

    def Randomize( self ):
        for line in self._matrix:
            for j in range( self.cols ):
                line[j] = randint( 0, self.rows )

    def __str__( self ):
        res = ""
        for line in self._matrix:
            sub_res = ""
            for i in range( len( line ) ):
                piece = "{" + str( i ) + ":9.2f} "
                sub_res += piece
            sub_res = sub_res.format( *line )
            sub_res += "\n"
            res += sub_res
        return res

    def __getitem__( self, item ):
        return self._matrix[item]

    def __add__( self, matrix ):
        if self.cols != matrix.cols or self.rows != matrix.rows:
            raise AssertionError( "Matrices should contain equal number of rows and columns." )

        res = Matrix( self.rows, self.cols )
        for i in range( self.rows ):
            for j in range( self.cols ):
                res._matrix[i][j] = self[i][j] + matrix[i][j]
        return res

    def __sub__( self, matrix ):
        if self.cols != matrix.cols or self.rows != matrix.rows:
            raise AssertionError( "Matrices should contain equal number of rows and columns." )

        res = Matrix( self.rows, self.cols )
        for i in range( self.rows ):
            for j in range( self.cols ):
                res[i][j] = self[i][j] - matrix[i][j]
        return res

    def __mul__( self, matrix):
        if self.cols != matrix.rows:
            raise AssertionError( "It's impossible to multiplicate this two matrices." )

        res = Matrix( cols=matrix.cols, rows=matrix.rows )
        for i in range( self.rows ):
            for j in range( matrix.cols ):
                res[i][j] = 0
                for k in range( self.cols ):
                    res[i][j] += self[i][k] * matrix[k][j]
        return res


if __name__ == '__main__':
    seed( 42 )
    m = Matrix( 2, 2 )
    n = Matrix( 2, 1 )
    m[0][1] = 1
    m[1][0] = 1
    n.Randomize()
    print( m )
    print( n )
    # print( "Add" )
    # print( m + n )
    # print( "Substract" )
    # print( m - n )
    print( "multiplicate" )
    print( m * n )
    # print( n * m )
