
from player import PPlayer


UNKNOWN_COMMAND     = -2
FOLD                = -1
CHECK               = 0
RAISE               = 1
CALL                = 2
SHOW                = 3

NEXT_TRADE_ROUND    = "ntr"
HAND_IS_OVER        = "hio"


class PTrade( object ):
    def __init__( self, players_l ):
        super( PTrade, self ).__init__()
        self._players_l = players_l
        self._main_pot  = 0
        self._max_stake = 0
        self._side_pots = []

    def CountActivePlayers( self ):
        res = 0
        for pl in self._players_l:
            if pl.active:
                res += 1
        return res


    def AreStakesEqual( self ):
        stake = None
        for pl in self._players_l:
            if pl.active and stake is None:
                stake = pl.stake
                continue
            if pl.stake != stake and pl.active:
                return False
        return True


    def AllMadeMove( self ):
        for pl in self._players_l:
            if not pl.made_move:
                return False
        return True


    def IsTradeFinished( self ):
        condition1 = self.CountActivePlayers() == 1
        condition2 = self.AllMadeMove() and self.AreStakesEqual()
        return condition1 or condition2


    def Trade( self ):
        current_player = 0
        while not self.IsTradeFinished():
            current_player %= len( self._players_l )
            if not self._players_l[current_player].active:
                current_player += 1
                continue
            print( "Current player is player #{0:2d}".format( current_player ) )
            player_action = self.ProcessInput()
            if player_action[0] == FOLD:
                self._players_l[current_player].SayFold()
            elif player_action[0] == CHECK:
                self._players_l[current_player].SayCheck()
            elif player_action[0] == RAISE:
                self._players_l[current_player].MakeStake(player_action[1])
                self._max_stake = self._players_l[current_player].stake
                self._main_pot += player_action[1]
            elif player_action[0] == CALL:
                cs = self._players_l[current_player].stake
                self._players_l[current_player].MakeStake( self._max_stake - cs )
                self._main_pot += self._max_stake - cs
            elif player_action[0] == SHOW:
                print( current_player )
                print( "Current Pot: {0:d}".format( self._main_pot ) )
                for player in self._players_l:
                    print(
                        "Stake: {0:4d} Stack: {1:4d}".format(
                            player.stake,
                            player.stack
                        ), player.active,
                        player.made_move
                    )
                print( "Stakes equal: ", self.AreStakesEqual() )
                continue
            elif player_action[0] == UNKNOWN_COMMAND:
                continue
            current_player += 1
        print(self.CountActivePlayers(), self._main_pot)


    def ProcessInput( self ):
        plin = input( "> " )
        if plin.lower() == "fold":
            return (FOLD, 0)
        elif plin.lower() =="check":
            return (CHECK, 0)
        elif plin.lower() == "raise":
            raisein = input( "Your stake: " )
            return (RAISE, int(raisein))
        elif plin.lower() == "call":
            return (CALL, 0)
        elif plin.lower() == "s" or plin.lower() == "show":
            return (SHOW, 0)
        else:
            return (UNKNOWN_COMMAND)


if __name__ == '__main__':
    l = [PPlayer() for i in range( 3 )]
    tr = PTrade( l )
    tr.Trade()
