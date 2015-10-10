from random import randint, choice

class Randomizer( object ):
    def __init__( self ):
        super( Randomizer, self ).__init__()

    @staticmethod
    def LoadedToss( probability ):
        toss = randint( 0, 99 )
        return toss < probability

    @staticmethod
    def EqualToss():
        coins = [True, False]
        return choice( coins )
