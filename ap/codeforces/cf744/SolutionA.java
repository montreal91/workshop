
import java.io.*;
import java.util.*;



public class SolutionA {
    public static void main(String[] args) throws Exception {
        function(new FastScanner(), System.out);
    }

    private static void function(final FastScanner in, final PrintStream out) throws Exception {
        int T = in.nextInt();
        String s;
        for (int i=0; i<T; i++) {
            s = in.next();
            yesOrNo(check(s), out);
        }
    }

    private static void yesOrNo(boolean b, final PrintStream out) {
        if (b) {
            out.println("YES");
        }
        else {
            out.println("NO");
        }
    }

    private static boolean check(String s) {
        int a = 0, b = 0, c = 0;
        char ch;
        for (int i=0; i<s.length(); i++) {
            ch = s.charAt(i);
            if (ch == 'A') {
                a++;
            }
            else if (ch == 'B') {
                b++;
            }
            else if (ch == 'C') {
                c++;
            }
        }
        return (a + c) == b;
    }
}

class FastScanner {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer("");

    String next() {
        while (!st.hasMoreTokens()) {
            try {
                st=new StringTokenizer(br.readLine());
            } catch (IOException e) {}
        }
        return st.nextToken();
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }
}
