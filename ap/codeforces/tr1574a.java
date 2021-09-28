
import java.io.*;
import java.util.*;



public class tr1574a {
    public static void main(String[] args) throws Exception {
        function(new FastScanner(), System.out);
    }

    private static void function(final FastScanner in, final PrintStream out) throws Exception {
        int N = in.nextInt();

        int a;
        for (int i=0; i<N; i++) {
            a = in.nextInt();
            subAnswer(a, out);
        }
    }

    private static String genPair(int a) {
        StringBuilder sb = new StringBuilder();

        for (int i=0; i<a; i++) {
            sb.append("(");
        }
        for (int i=0; i<a; i++) {
            sb.append(")");
        }
        return sb.toString();
    }

    private static void subAnswer(int a, final PrintStream out) {
        for (int i=0; i<a; i++) {
            out.println(genPair(i) + genPair(a - i));
        }
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
