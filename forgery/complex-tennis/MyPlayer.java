public class MyPlayer {
    public final MyName name;

    private MyServe     first_serve;
    private MyServe     second_serve;

    private int         game_points_won;
    private int         total_points_won;
    private int         games_won;
    private int         sets_won;

    private int         games_on_serve;
    private int         double_faults;
    private int         serves_lost;

    private boolean     serving;

    public final int    WON             = 1;
    public final int    LOST            = -1;
    public final int    DOUBLE_FAULT    = -2;

    public MyPlayer(){
        this.name               = new MyName();

        this.first_serve        = new MyServe();
        this.second_serve       = new MyServe();

        this.game_points_won    = 0;
        this.total_points_won   = 0;
        this.games_won          = 0;
        this.sets_won           = 0;

        this.games_on_serve     = 0;
        this.double_faults      = 0;
        this.serves_lost        = 0;

        this.serving            = false;
    }

    public MyPlayer( MyName name, MyServe first_serve, MyServe second_serve ){
        this.name               = name;

        this.first_serve        = first_serve;
        this.second_serve       = second_serve;

        this.game_points_won    = 0;
        this.total_points_won   = 0;
        this.games_won          = 0;
        this.sets_won           = 0;

        this.games_on_serve     = 0;
        this.double_faults      = 0;
        this.serves_lost        = 0;

        this.serving            = false;
    }

    public void WinPoint(){
        this.game_points_won++;
        this.total_points_won++;
    }

    public void DropGamePoints(){
        this.game_points_won = 0;
    }

    public int GetGamePoints(){
        return this.game_points_won;
    }

    public int GetTotalPoints(){
        return this.total_points_won;
    }

    public void WinGame(){
        this.games_won++;
    }

    public void DropGames(){
        this.games_won = 0;
    }

    public int GetGamesWon(){
        return this.games_won;
    }

    public void WinSet(){
        this.sets_won++;
    }

    public int GetSetsWon(){
        return this.sets_won;
    }

    public void MakeDoubleFault(){
        this.double_faults++;
    }

    public int GetDoubleFaults(){
        return this.double_faults;
    }

    public void LooseServiceGame(){
        this.serves_lost++;
    }

    public int GetLostServes(){
        return this.serves_lost;
    }

    public void ToServe(){
        this.serving = true;
    }

    public void EndServe(){
        this.serving = false;
    }

    public boolean IsServing(){
        return this.serving;
    }

    public int PlayPoint(){
        Randomizer rand             = new Randomizer( );
        boolean first_serve_in      = rand.LoadedToss( this.first_serve.GetServeInPercent() );
        boolean second_serve_in     = rand.LoadedToss( this.second_serve.GetServeInPercent() );

        if ( first_serve_in ){
            boolean point = rand.LoadedToss( this.first_serve.GetServePointsWon() );
            if ( point ){
                return WON;
            } else {
                return LOST;
            }
        } else {
            if ( second_serve_in ){
                boolean point = rand.LoadedToss( this.second_serve.GetServePointsWon() );
                if ( point ){
                    return WON;
                } else {
                    return LOST;
                }
            } else {
                return DOUBLE_FAULT;
            }
        }
    }
}
