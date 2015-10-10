public class MyTennisMatch{
    private MyPlayer player_one;
    private MyPlayer player_two;
    
    private String match_result; 

    private final int POINTS_TO_WIN_GAME;
    private final int POINTS_TO_WIN_TIEBREAK;
    private final int GAMES_TO_WIN_SET;
    private final int SETS_TO_WIN_MATCH;

    private final boolean TIEBREAKS;
    private final boolean FINAL_SET_TIEBREAK;

    private final boolean GAME          = false;
    private final boolean SET_TIEBREAK  = true;


    public MyTennisMatch( ){
        this.player_one                 = new MyPlayer( );
        this.player_two                 = new MyPlayer( );

        this.match_result               = "";

        this.POINTS_TO_WIN_GAME         = 4;
        this.POINTS_TO_WIN_TIEBREAK     = 7;
        this.GAMES_TO_WIN_SET           = 6;
        this.SETS_TO_WIN_MATCH          = 3;

        this.TIEBREAKS                  = true;
        this.FINAL_SET_TIEBREAK         = false;

        Randomizer random               = new Randomizer( );
        if ( random.EqualToss() ){
            player_one.ToServe();
        } else {
            player_two.ToServe();
        }
    }

    public MyTennisMatch (  MyPlayer player_one,
                            MyPlayer player_two,
                            int points_to_win_game,
                            int points_to_win_tiebreak,
                            int games_to_win_set,
                            int sets_to_win_match,
                            boolean tiebreaks,
                            boolean last_set_tiebreak
                        ){
        this.player_one                 = player_one;
        this.player_two                 = player_two;

        this.match_result               = "";

        this.POINTS_TO_WIN_GAME         = points_to_win_game;
        this.POINTS_TO_WIN_TIEBREAK     = points_to_win_tiebreak;
        this.GAMES_TO_WIN_SET           = games_to_win_set;
        this.SETS_TO_WIN_MATCH          = sets_to_win_match;

        this.TIEBREAKS                  = tiebreaks;

        Randomizer random               = new Randomizer( );
        if ( random.EqualToss() ){
            player_one.ToServe();
        } else {
            player_two.ToServe();
        }

        if ( !this.TIEBREAKS ){
            this.FINAL_SET_TIEBREAK = false;
        } else {
            this.FINAL_SET_TIEBREAK = last_set_tiebreak;   
        }
    }

    private void PlayGame(){
        while ( true ){
            if ( this.player_one.IsServing() ){
                int point = this.player_one.PlayPoint();
                if ( point == this.player_one.WON ){
                    this.player_one.WinPoint();
                } else if ( point == this.player_one.LOST ){
                    this.player_two.WinPoint();
                } else if ( point == this.player_one.DOUBLE_FAULT ) {
                    this.player_one.MakeDoubleFault();
                    this.player_two.WinPoint();
                }
            } else if ( this.player_two.IsServing() ){
                int point = this.player_two.PlayPoint();
                if ( point == this.player_two.WON ){
                    this.player_two.WinPoint();
                } else if ( point == this.player_two.LOST ){
                    this.player_one.WinPoint();
                } else if ( point == this.player_two.DOUBLE_FAULT ){
                    this.player_two.MakeDoubleFault();
                    this.player_one.WinPoint();
                }
            } else {
                // actually we should raise an error
            }

            if ( this.CheckIsGameOver( this.GAME ) ){
                break;
            } else {
                continue;
            }
        }

        if ( this.player_one.GetGamePoints() > this.player_two.GetGamePoints() ){
            this.player_one.WinGame();
            if ( this.player_two.IsServing() ){
                this.player_two.LooseServiceGame();
            }
        } else {
            this.player_two.WinGame();
            if ( this.player_one.IsServing() ){
                this.player_one.LooseServiceGame();
            }
        }

        this.player_one.DropGamePoints();
        this.player_two.DropGamePoints();
    }

    public String PlayTiebreak(){
        for ( int i = 1; true; i++ ){
            if ( this.player_one.IsServing() ){
                int point = this.player_one.PlayPoint();
                if ( point == this.player_one.WON ){
                    this.player_one.WinPoint();
                } else if ( point == this.player_one.LOST ){
                    this.player_two.WinPoint();
                } else if ( point == this.player_one.DOUBLE_FAULT ) {
                    this.player_one.MakeDoubleFault();
                    this.player_two.WinPoint();
                }
            } else if ( this.player_two.IsServing() ){
                int point = this.player_two.PlayPoint();
                if ( point == this.player_two.WON ){
                    this.player_two.WinPoint();
                } else if ( point == this.player_two.LOST ){
                    this.player_one.WinPoint();
                } else if ( point == this.player_two.DOUBLE_FAULT ){
                    this.player_two.MakeDoubleFault();
                    this.player_one.WinPoint();
                }
            }
            if ( i % 2 == 1 ){
                this.SwitchServer();
            }
            if ( this.CheckIsGameOver( this.SET_TIEBREAK ) ){
                break;
            } else {
                continue;
            }
        }
        if ( this.player_one.GetGamePoints() > this.player_two.GetGamePoints() ){
            this.player_one.WinGame();
        } else {
            this.player_two.WinGame();
        }
        int points_one = this.player_one.GetGamePoints();
        int points_two = this.player_two.GetGamePoints();
        this.player_one.DropGamePoints();
        this.player_two.DropGamePoints();
        return "(" + points_one + ":" + points_two + ")";
    }

    public void PlaySet(){
        String tiebreak_result = "";
        while ( true ){
            this.PlayGame();
            this.SwitchServer();
            if ( this.CheckTieBreakCondition() ){
                tiebreak_result = this.PlayTiebreak();
                break;
            }
            if ( this.CheckIsSetOver() ){
                break;
            } else {
                continue;
            }
        }

        if ( this.player_one.GetGamesWon() > this.player_two.GetGamesWon() ){
            this.player_one.WinSet();
        } else {
            this.player_two.WinSet();
        }

        int games_one = this.player_one.GetGamesWon();
        int games_two = this.player_two.GetGamesWon();
        this.match_result += ( games_one + ":" + games_two + tiebreak_result + " " );
        this.player_one.DropGames();
        this.player_two.DropGames();
    }

    public void PlayMatch(){
        while ( !this.CheckIsMatchOver() ){
            this.PlaySet();
        }
        this.PrintStats();
        System.out.println( this.match_result );
    }

    private boolean CheckIsGameOver( boolean flag ){
        int points_one          = this.player_one.GetGamePoints();
        int points_two          = this.player_two.GetGamePoints();
        boolean condition_one   = Math.abs( points_one - points_two ) >= 2;
        boolean condition_two;
        if ( flag == this.GAME ){
            condition_two = ( points_one >= this.POINTS_TO_WIN_GAME ) || ( points_two >= this.POINTS_TO_WIN_GAME );
        } else {
            condition_two = ( points_one >= this.POINTS_TO_WIN_TIEBREAK ) || ( points_two >= this.POINTS_TO_WIN_TIEBREAK );
        }
        return condition_one && condition_two;
    }

    private boolean CheckIsSetOver(){
        int games_one = this.player_one.GetGamesWon();
        int games_two = this.player_two.GetGamesWon();
        boolean condition_one = Math.abs( games_one - games_two ) >= 2;
        boolean condition_two = ( games_one >= this.GAMES_TO_WIN_SET ) || ( games_two >= this.GAMES_TO_WIN_SET );
        return condition_one && condition_two;
    }

    private boolean CheckIsMatchOver(){
        int sets_one = this.player_one.GetSetsWon();
        int sets_two = this.player_two.GetSetsWon();
        return ( sets_one == this.SETS_TO_WIN_MATCH ) || ( sets_two == this.SETS_TO_WIN_MATCH ); 
    }

    private boolean CheckTieBreakCondition(){
        int games_one = this.player_one.GetGamesWon();
        int games_two = this.player_two.GetGamesWon();
        int sets_one = this.player_one.GetSetsWon();
        int sets_two = this.player_two.GetSetsWon();
        boolean condition = ( games_one == games_two ) && ( games_one == this.GAMES_TO_WIN_SET );
        boolean final_set = ( sets_one + sets_two ) == ( this.SETS_TO_WIN_MATCH * 2 - 2 );

        if ( condition && !final_set && this.TIEBREAKS ){
            return true;
        } else if ( condition && final_set && this.FINAL_SET_TIEBREAK ){
            return true;
        } else {
            return false;
        }
    }

    private void SwitchServer(){
        if ( this.player_one.IsServing() ){
            this.player_one.EndServe();
            this.player_two.ToServe();
        } else if ( this.player_two.IsServing() ){
            this.player_two.EndServe();
            this.player_one.ToServe();
        } else {
            // Actually we should raise an error;
        }
    }

    // this function is wrote for testing purpouses only
    // in release version shoud be removed
    private void PrintStats(){
        int sets_one            = this.player_one.GetSetsWon();
        int sets_two            = this.player_two.GetSetsWon();
        int total_points_one    = this.player_one.GetTotalPoints();
        int total_points_two    = this.player_two.GetTotalPoints();
        int double_faults_one   = this.player_one.GetDoubleFaults();
        int double_faults_two   = this.player_two.GetDoubleFaults();
        int serves_lost_one     = this.player_one.GetLostServes();
        int serves_lost_two     = this.player_two.GetLostServes();

        String name_one         = this.player_one.name.GetShortedName();
        String name_two         = this.player_two.name.GetShortedName();

        System.out.printf( "                  %s - %s\n", name_one, name_two );
        System.out.printf( "Sets Won         : %3d - %3d\n", sets_one, sets_two );
        System.out.printf( "Double Faults    : %3d - %3d\n", double_faults_one, double_faults_two );
        System.out.printf( "Lost Serves      : %3d - %3d\n", serves_lost_one, serves_lost_two );
        System.out.printf( "Total Points Won : %3d - %3d\n", total_points_one, total_points_two );
    }

}
