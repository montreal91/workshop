public class MyServe {
    private int serve_in_percent; // Percentage of successive serves
    private int serve_points_won;

    public MyServe(){
        this.serve_in_percent   = 50;
        this.serve_points_won   = 50;
    }

    public MyServe( int serve_in_percent, int serve_points_won ){
        this.serve_in_percent   = serve_in_percent;
        this.serve_points_won   = serve_points_won;
    }

    public int GetServeInPercent(){
        return this.serve_in_percent;
    }

    public int GetServePointsWon(){
        return this.serve_points_won;
    }
}
