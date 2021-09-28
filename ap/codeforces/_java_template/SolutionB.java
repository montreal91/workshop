
import java.io.*;
import java.util.*;



public class SolutionB {
    public static void main(String[] args) throws Exception {
        function(new FastScanner(), System.out);
    }

    private static void function(final FastScanner in, final PrintStream out) throws Exception {
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
