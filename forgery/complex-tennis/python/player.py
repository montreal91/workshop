
from name           import MyName
from serve          import MyServe
from randomizer     import Randomizer

WON             = 1
LOST            = -1
DOUBLE_FAULT    = -2

class MyPlayer( object ):
    """docstring for MyPlayer"""
    def __init__( self, name=MyName(), first_serve=MyServe(), second_serve=MyServe() ):
        super( MyPlayer, self ).__init__()
        assert type( name )         == MyName
        assert type( first_serve )  == MyServe
        assert type( second_serve ) == MyServe

        self.__name                     = name
        self.__first_serve              = first_serve
        self.__second_serve             = second_serve

        self.__game_points_won          = 0
        self.__total_points_won         = 0
        self.__games_won                = 0
        self.__total_games_won          = 0
        self.__sets_won                 = 0

        self.__games_on_serve           = 0
        self.__double_faults            = 0
        self.__serves_lost              = 0

        self.__service_points_played    = 0
        self.__service_points_won       = 0
        
        self.__serving                  = False


    def __str__( self ):
        res = self.name.first_name[ 0 ] + ". " + self.name.last_name + " | "
        res += str( self.__first_serve.accuracy ) + " | " + str( self.__first_serve.quality ) + " | "
        res += str( self.__second_serve.accuracy ) + " | " + str( self.__second_serve.quality )
        return res

    @property 
    def name( self ):
        return self.__name


    @property
    def first_serve( self ):
        return self.__first_serve


    @property
    def second_serve( self ):
        return self.__second_serve
    

    @property 
    def game_points_won( self ):
        return self.__game_points_won

    @property 
    def total_points_won( self ):
        return self.__total_points_won

    @property 
    def games_won( self ):
        return self.__games_won

    @property
    def total_games_won( self ):
        return self.__total_games_won
    

    @property 
    def sets_won( self ):
        return self.__sets_won

    @property 
    def games_on_serve( self ):
        return self.__games_on_serve


    @property 
    def double_faults( self ):
        return self.__double_faults


    @property
    def service_points_played( self ):
        return self.__service_points_played


    @property
    def service_points_won( self ):
        return self.__service_points_won
    

    @property 
    def serves_lost( self ):
        return self.__serves_lost

    @property 
    def serving( self ):
        return self.__serving

    def WinPoint( self ):
        self.__game_points_won += 1
        self.__total_points_won += 1
        if self.__serving:
            self.__service_points_won += 1

    def DropGamePoints( self ):
        self.__game_points_won = 0

    def WinGame( self ):
        self.__games_won += 1
        self.__total_games_won += 1

    def DropGames( self ):
        self.__games_won = 0

    def WinSet( self ):
        self.__sets_won += 1

    def MakeDoubleFault( self ):
        self.__double_faults += 1

    def LooseServiceGame( self ):
        self.__serves_lost += 1

    def ToServe( self ):
        self.__serving = True

    def EndServe( self ):
        self.__serving = False

    def AddGameOnServe( self ):
        self.__games_on_serve += 1

    def PlayPoint( self ):
        first_serve_in = Randomizer.LoadedToss(self.__first_serve.accuracy)
        second_serve_in = Randomizer.LoadedToss(self.__second_serve.accuracy)
        self.__service_points_played += 1

        if first_serve_in is True:
            point = Randomizer.LoadedToss(self.__first_serve.quality)
            if point is True:
                return WON
            else:
                return LOST
        elif second_serve_in is True:
            point = Randomizer.LoadedToss(self.__second_serve.quality)
            if point is True:
                return WON
            else:
                return LOST
        else:
            return DOUBLE_FAULT


    def DropEverything( self ):
        self.__game_points_won  = 0
        self.__total_points_won = 0
        self.__games_won        = 0
        self.__total_games_won  = 0
        self.__sets_won         = 0

        self.__games_on_serve   = 0
        self.__double_faults    = 0
        self.__serves_lost      = 0

        self.__service_points_played = 0
        self.__service_points_won = 0
        
        self.__serving          = False
