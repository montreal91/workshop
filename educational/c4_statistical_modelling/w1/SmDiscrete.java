
import java.lang.Math;
import java.math.BigInteger;

public class SmDiscrete {
    private final static int EXPERIMENT_ITERATIONS = 100000;
    public static void main( String[] args ) {
        numericExperiment(30, 0.25);
    }
    
    private static void numericExperiment(int N, double p) {
        int[] results = new int[N+1];
        System.out.println("Experiment started");
        System.out.println("------------------\n");
        for (int i = 0; i < EXPERIMENT_ITERATIONS; i++) {
            int dv = getDiscreteNormalDistribution(p, N);
            results[dv] += 1;
        }
        
        for (int i = 0; i < results.length; i++) {
            System.out.format("%3d: %d\n", i, results[i]);
        }
    }

    private static int getDiscreteNormalDistribution(double p_success, int n_iterations) {
        double var = Math.random();
        double f = 0;
        int i=0;
        do {
            f += calculateBinomialProbability(p_success, n_iterations, i);
            i++;
        } while (f < var);
        return i-1;
    }
    
    public static int getPoissonDistribution(double lambda) {
        double var = Math.random();
        double f = 0;
        int i = 0;
        do {
            f += calculatePoissonProbability(lambda, i);
            i++;
        } while ( f < var);
        return i - 1;
    }

    private static long getNumberOfCombinations(int from_n, int by_k) {
        BigInteger nominator = getFactorial(from_n);
        BigInteger k_fac = getFactorial(by_k);
        BigInteger n_minus_k_fac = getFactorial(from_n - by_k);
        BigInteger denominator = k_fac.multiply(n_minus_k_fac);
        BigInteger res = nominator.divide(denominator);
        return res.longValue();
    }

    private static double calculateBinomialProbability(double p_success, int n_iterations, int m_successes) {
        double c = getNumberOfCombinations(n_iterations, m_successes);
        double p = Math.pow(p_success, m_successes);
        double q = Math.pow(1.0 - p_success, n_iterations - m_successes);
        return c * p * q;
    }

    private static BigInteger getFactorial(int n) {
        if (n == 0) {
            return new BigInteger("1");
        }
        BigInteger res = new BigInteger("1");
        BigInteger on_step = new BigInteger("1");
        for (int i = 1; i <= n; i++) {
            on_step = new BigInteger(Integer.toString(i));
            res = res.multiply(on_step);
        }
        return res;
    }
    
    private static double calculatePoissonProbability(double l_param, int k_value) {
        double nom = Math.exp(-l_param) * Math.pow(l_param, k_value);
        Double denom = new Double(getFactorial(k_value).toString());
        return nom / denom.doubleValue();
    }
}
