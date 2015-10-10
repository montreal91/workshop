import java.util.Random;

public class Randomizer {
    private Random random;

    public Randomizer( ) {
        this.random = new Random( );
    }

    public boolean LoadedToss( int percentage ){
        double probability  = ( double ) percentage / 100;
        double toss         = this.random.nextDouble( );
        return toss < probability;
    }

    public boolean EqualToss( ){
        return this.random.nextBoolean( );
    }
}
