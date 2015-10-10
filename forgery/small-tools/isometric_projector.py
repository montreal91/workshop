
import sys

def PrintIsometricProjection( x, y, z ):
    print( 0.7071 * ( x -z ) )
    print( 0.4082 * ( x - 2 * y + z ) )


if __name__ == '__main__':
    try:
        x = float( sys.argv[ 1 ] )
        y = float( sys.argv[ 2 ] )
        z = float( sys.argv[ 3 ] )
        PrintIsometricProjection( x, y, z )
    except IndexError:
        print( "Please, enter correct 3D-point." )
    except ValueError:
        print( "All vertices should be numbers." )
