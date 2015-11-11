
import sys
import time

from random import shuffle

def ShuffleList( some_list ):
    for i in range( 10 ):
        print( 10-i )
        time.sleep( 1 )
    print( "Shuffling" )
    shuffle( some_list )
    print()
    for item in some_list:
        print( item )

if __name__ == '__main__':
    ShuffleList( sys.argv[1:] )
