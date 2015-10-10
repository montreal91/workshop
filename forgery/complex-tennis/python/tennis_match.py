from player     import MyPlayer
from player     import WON, LOST, DOUBLE_FAULT
from randomizer import Randomizer

class MyTennisMatch( object ):
    """docstring for MyTennisMatch"""
    def __init__(
        self, 
        player_one=MyPlayer(), 
        player_two=MyPlayer(), 
        points_to_win_game=4, 
        points_to_win_tiebreak=7,
        games_to_win_set=6,
        sets_to_win_match=3,
        tiebreaks=True,
        final_set_tiebreak=False 
    ):
        super( MyTennisMatch, self ).__init__()
        self.__player_one               = player_one
        self.__player_two               = player_two

        self.__POINTS_TO_WIN_GAME       = points_to_win_game
        self.__POINTS_TO_WIN_TIEBREAK   = points_to_win_tiebreak
        self.__GAMES_TO_WIN_SET         = games_to_win_set
        self.__SETS_TO_WIN_MATCH        = sets_to_win_match

        self.__TIEBREAKS                = tiebreaks

        self.__result                   = []
        
        if self.__TIEBREAKS is False:
            self.__FINAL_SET_TIEBREAK = False
        else:
            self.__FINAL_SET_TIEBREAK = final_set_tiebreak

        if Randomizer.EqualToss() is True:
            self.__player_one.ToServe()
        else:
            self.__player_two.ToServe() 


    def PlayGame( self, playing_tiebreak=False ):
        self.__player_one.DropGamePoints()
        self.__player_two.DropGamePoints()

        if not playing_tiebreak and self.__player_one.serving:
            self.__player_one.AddGameOnServe()
        elif not playing_tiebreak and self.__player_two.serving:
            self.__player_two.AddGameOnServe()
        elif playing_tiebreak:
            pass
        else:
            raise StandardError

        while self.__CheckIsGameOver( playing_tiebreak ) is not True:
            if self.__player_one.serving is True:
                point = self.__player_one.PlayPoint()
                if point == WON:
                    self.__player_one.WinPoint()
                elif point == LOST:
                    self.__player_two.WinPoint()
                elif point == DOUBLE_FAULT:
                    self.__player_one.MakeDoubleFault()
                    self.__player_two.WinPoint()
                else:
                    raise StandardError( "Unexpected point value." )
            elif self.__player_two.serving is True:
                point = self.__player_two.PlayPoint()
                if point == WON:
                    self.__player_two.WinPoint()
                elif point == LOST:
                    self.__player_one.WinPoint()
                elif point == DOUBLE_FAULT:
                    self.__player_two.MakeDoubleFault()
                    self.__player_one.WinPoint()
                else:
                    raise StandardError( "Unexpected point value." )
            else:
                raise StandardError( "Both players are not serving." )

            if playing_tiebreak and self.__CheckTiebreakSwitchingServerCondition() is True:
                self.__SwitchServer()

        # Afterparty
        if self.__player_one.game_points_won > self.__player_two.game_points_won:
            self.__player_one.WinGame()
            if self.__player_two.serving is True and not playing_tiebreak:
                self.__player_two.LooseServiceGame()
        else:
            self.__player_two.WinGame()
            if self.__player_one.serving is True and not playing_tiebreak:
                self.__player_one.LooseServiceGame()
        return self.__player_one.game_points_won, self.__player_two.game_points_won

    def PlaySet( self ):
        self.__player_one.DropGames()
        self.__player_two.DropGames()
        result = []

        while self.__CheckIsSetOver() is not True:
            result.append( self.PlayGame() )
            self.__SwitchServer()
            if self.__CheckTiebreakCondition() is True:
                result.append( self.PlayGame( playing_tiebreak=True ) )
                break

        if self.__player_one.games_won > self.__player_two.games_won:
            self.__player_one.WinSet()
        else:
            self.__player_two.WinSet()

        return { ( self.__player_one.games_won, self.__player_two.games_won ): result }

    def PlayMatch( self ):
        while self.__CheckIsMatchOver() is not True:
            self.__result.append( self.PlaySet() )
        return self.__result

    def __SwitchServer( self ):
        if self.__player_one.serving is True:
            self.__player_one.EndServe()
            self.__player_two.ToServe()
        elif self.__player_two.serving is True:
            self.__player_two.EndServe()
            self.__player_one.ToServe()
        else:
            raise StandardError( "Both players are not serving." )

    def __CheckIsGameOver( self, playing_tiebreak=False ):
        points_one      = self.__player_one.game_points_won
        points_two      = self.__player_two.game_points_won
        if playing_tiebreak is False:
            points_to_win = self.__POINTS_TO_WIN_GAME
        else:
            points_to_win = self.__POINTS_TO_WIN_TIEBREAK
        condition_one   = abs( points_one - points_two ) >= 2
        condition_two   = points_one >= points_to_win or points_two >= points_to_win
        return condition_one and condition_two

    def __CheckIsSetOver( self ):
        games_one       = self.__player_one.games_won 
        games_two       = self.__player_two.games_won
        condition_one   = abs(games_one - games_two) >= 2
        condition_two   = games_one >= self.__GAMES_TO_WIN_SET or games_two >= self.__GAMES_TO_WIN_SET
        return condition_one and condition_two

    def __CheckIsMatchOver( self ):
        return self.__player_one.sets_won == self.__SETS_TO_WIN_MATCH or self.__player_two.sets_won == self.__SETS_TO_WIN_MATCH

    def __CheckTiebreakCondition( self ):
        condition = self.__player_one.games_won == self.__player_two.games_won == self.__GAMES_TO_WIN_SET
        final_set = self.__player_one.sets_won + self.__player_two.sets_won == self.__SETS_TO_WIN_MATCH * 2 - 2
        if not final_set and condition and self.__TIEBREAKS:
            return True
        elif final_set and condition and self.__FINAL_SET_TIEBREAK:
            return True
        else:
            return False

    def __CheckTiebreakSwitchingServerCondition( self ):
        return ( self.__player_one.game_points_won + self.__player_two.game_points_won ) % 2 == 1

    @property 
    def match_title( self ):
        return self.__player_one.name.full_name + " vs " + self.__player_two.name.full_name

    @property 
    def sets_won( self ):
        return self.__player_one.sets_won, self.__player_two.sets_won

    @property 
    def final_score( self ):
        res = ""
        for a_set in self.__result:
            for score in a_set:
                res += "{0:1d}:{1:1d}".format( score[0], score[1] )
                if abs( score[0] - score[1] ) == 1:
                    res += " ({0:1d}:{1:1d})".format( a_set[score][-1][0], a_set[score][-1][1] )
                res += "; "
        return res

    @property 
    def total_points_won( self ):
        return self.__player_one.total_points_won, self.__player_two.total_points_won

    @property
    def service_points_played( self ):
        return self.__player_one.service_points_played, self.__player_two.service_points_played


    @property
    def service_points_won( self ):
        return self.__player_one.service_points_won, self.__player_two.service_points_won


    @property
    def total_games_won( self ):
        return self.__player_one.total_games_won, self.__player_two.total_games_won
    

    @property 
    def games_on_serve( self ):
        return self.__player_one.games_on_serve, self.__player_two.games_on_serve

    @property 
    def brakes( self ):
        return self.__player_two.serves_lost, self.__player_one.serves_lost

    @property 
    def double_faults( self ):
        return self.__player_one.double_faults, self.__player_two.double_faults

    @property 
    def result( self ):
        return self.__result
