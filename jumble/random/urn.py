
from random import randint, random

def TestUrnScheme():
    ss, su, uu = 0, 0, 0
    total = 100000
    for i in range( total ):
        l = ["s", "s", "u", "u"]
        s = l.pop( randint( 0, 3 ) ) + l.pop( randint( 0, 2 ) )
        if s == "ss":
            ss += 1
        elif s == "su" or s == "us":
            su += 1
        elif s == "uu":
            uu += 1
    print( "P(ss) = {0:.4f}".format( ss / total ) )
    print( "P(su) = {0:.4f}".format( su / total ) )
    print( "P(uu) = {0:.4f}".format( uu / total ) )

def GetDiscreteRandomValue( probs_list ):
    x = random()
    for i in range( len( probs_list ) ):
        if x < sum( probs_list[:i+1] ):
            return i

def TestDRV():
    pl = [1/14, 3/7, 3/7, 1/14, 0]
    s0, s1, s2, s3, s4 = 0, 0, 0, 0, 0
    total = 100000
    for i in range( total ):
        xi = GetDiscreteRandomValue( pl )
        if xi == 0:
            s0 += 1
        elif xi == 1:
            s1 += 1
        elif xi == 2:
            s2 += 1
        elif xi == 3:
            s3 += 1
        elif xi == 4:
            s4 += 1
    print( "P(xi=0) = {0:.4f}".format( s0 / total ) )
    print( "P(xi=1) = {0:.4f}".format( s1 / total ) )
    print( "P(xi=2) = {0:.4f}".format( s2 / total ) )
    print( "P(xi=3) = {0:.4f}".format( s3 / total ) )
    print( "P(xi=4) = {0:.4f}".format( s4 / total ) )

if __name__ == '__main__':
    # TestUrnScheme()
    TestDRV()
    # pl = [1/14, 3/7, 3/7, 1/14, 0]
    # for i in range( 20 ):
    #     print( GetDiscreteRandomValue(pl))
