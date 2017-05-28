import java.lang.Math;


public class SmMonteCarlo {
    private static double getIntegralValue(int num) {
        double sum = 0;
        for (int i = 0; i < num; i++) {
            double cv = SmContinious.getExpRandomValue(1);
            sum += (Math.sin(cv + 1) * Math.exp(-cv * cv - cv - 1));
        }
        return sum / num;
    }

    public static void main(String[] args) {
        System.out.println(getIntegralValue(10000000));
    }
}
