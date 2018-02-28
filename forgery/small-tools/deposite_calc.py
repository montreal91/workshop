import sys

def deposite_calc( start, interest, addition=0 ):
    res = start
    for i in range( 5 ):
        res *= interest
        res += addition
    print( "Sum after five years: {0:9.2f} Diff: {1:9.2f}".format( res, res - start - addition * 5 ) )

    for i in range( 5 ):
        res *= interest
        res += addition
    print( "Sum after ten years : {0:9.2f} Diff: {1:9.2f}".format( res, res - start - addition * 10 ) )

if __name__ == '__main__':
    try:
        start = float(sys.argv[1])
        interest = float(sys.argv[2])
        if len( sys.argv ) == 3:
            deposite_calc( start, interest )
        else:
            addition = float(sys.argv[3])
            deposite_calc( start, interest, addition=addition )
    except IndexError:
        print( "You should enter starting value and an interest." )
    except ValueError:
        print( "Your input should be correct numbers." )
