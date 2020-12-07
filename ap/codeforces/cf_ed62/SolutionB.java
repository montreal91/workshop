//
// https://codeforces.com/contest/1140/problem/B
// Author: montreal91
// Type: training
// Time: 00:20
// Failed attempts: 0
//
import java.util.Scanner;

public class SolutionB {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        int n;
        String s;
        for (int i=0; i<T; i++) {
            n = in.nextInt();
            s = in.next();
            System.out.println(solveString(s));
        }
    }

    private static int solveString(String s) {
        return Math.min(findLeft(s), findRight(s));
    }

    private static int findLeft(String s) {
        int i = 0;
        for (i=0; i<s.length(); i++) {
            if (s.charAt(i) == '>') {
                return i;
            }
        }
        return i;
    }

    private static int findRight(String s) {
        int i=0;
        for (i=0; i<s.length(); i++) {
            if (s.charAt(s.length() - i - 1) == '<') {
                return i;
            }
        }
        return i;
    }
}
