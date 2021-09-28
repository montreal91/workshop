
import java.io.*;
import java.util.*;



public class SolutionB {
    public static void main(String[] args) throws Exception {
        function(new FastScanner(), System.out);
    }

    private static void function(final FastScanner in, final PrintStream out) throws Exception {
        int T = in.nextInt();
        for (int i=0; i<T; i++) {
            var numbers = new ArrayList<Long>();
            int N = in.nextInt();
            for (int j=0; j<N; j++) {
                numbers.add(in.nextLong());
            }
            printResult(solve(numbers), out);
        }
    }

    private static ArrayList<Operation> solve(ArrayList<Long> numbers) {
        var copy = new ArrayList<Long>(numbers);
        Collections.sort(copy);

        var result = new ArrayList<Operation>();
        for (int i=0; i<numbers.size(); i++) {
            // System.out.println(numbers);
            // System.out.println(copy);
            // System.out.println("");
            if (numbers.get(i) == copy.get(i)) {
                continue;
            }
            for (int j=i+1; j<numbers.size(); j++) {
                if (copy.get(i) == numbers.get(j)) {
                    result.add(new Operation(i+1, j+1));
                    doShift(numbers, i, j);
                    break;
                }
            }
        }
        return result;
    }

    private static void printResult(List<Operation> result, PrintStream out) {
        out.println(result.size());
        for (var r : result) {
            out.print(r.left);
            out.print(" ");
            out.print(r.right);
            out.print(" ");
            out.print(r.right - r.left);
            out.print("\n");
        }
    }

    private static void doShift(ArrayList<Long> numbers, int left, int right) {
        long prev = numbers.get(left);
        long tmp = 0;
        for (int i=left+1; i<=right; i++) {
            tmp = numbers.get(i);
            numbers.set(i, prev);
            prev = tmp;
        }
        numbers.set(left, prev);
    }
}

class Operation {
    int left, right;

    Operation(int left, int right) {
        this.left = left;
        this.right = right;
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
