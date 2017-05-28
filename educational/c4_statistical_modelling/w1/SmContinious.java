
import java.lang.Math;

public class SmContinious {
    final private static int P_DENOM = 4;

    private static int getDiscreteRandomValue() {
        double a = Math.random();
        if (a < (1.0 / P_DENOM)) {
            return 0;
        } else {
            return 1;
        }
    }

    public static double getExpRandomValue(double lambda) {
        return (-1.0 / lambda) * Math.log(Math.random());
    }

    private static double getRandomValue() {
        int d_val = getDiscreteRandomValue();
        if (d_val == 0) {
            return getExpRandomValue(3);
        } else {
            return getExpRandomValue(1);
        }
    }

    public static void main(String[] args) {
        System.out.println(getRandomValue());
    }
}
