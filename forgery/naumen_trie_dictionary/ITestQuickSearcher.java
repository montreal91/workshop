
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;


public class ITestQuickSearcher {
    private static String[] names = new String[100000];
    private static long[] dates = new long[100000];

    private static String[] sstrings2 = new String[10];
    private static String[] sstrings3 = new String[10];
    private static String[] sstrings4 = new String[10];


    public static void main(String[] args) throws FileNotFoundException {
        loadData();
        loadGuessStrings();

        ITrieSearcher qs = new ITrieSearcher();
        long startRefreshTime = System.nanoTime();
        qs.refresh(names, dates);
        long endRefreshTime = System.nanoTime();
        System.out.format("Refresh Duration: %f ms.\n", (endRefreshTime - startRefreshTime) / 1000000.0);

        long total2duration = 0;
        long total3duration = 0;
        long total4duration = 0;
        for (int i = 0; i < 10; i++) {
            long start = System.nanoTime();
            qs.guess(sstrings2[i]);
            long end = System.nanoTime();
            total2duration += (end - start);

            start = System.nanoTime();
            qs.guess(sstrings3[i]);
            end = System.nanoTime();
            total3duration += (end - start);

            start = System.nanoTime();
            qs.guess(sstrings4[i]);
            end = System.nanoTime();
            total4duration += (end - start);
        }
        double average2 = total2duration / 10.0;
        double average3 = total3duration / 10.0;
        double average4 = total4duration / 10.0;

        System.out.format("\nAverage search with 2-char guess string: %f ms.\n", average2 / 1000000.0);
        System.out.format("Average search with 3-char guess string: %f ms.\n", average3 / 1000000.0);
        System.out.format("Average search with 4-char guess string: %f ms.\n", average4 / 1000000.0);
    }

    private static void loadData() throws FileNotFoundException  {
        BufferedReader nameReader = new BufferedReader(new FileReader("names.txt"));
        BufferedReader numReader = new BufferedReader(new FileReader("numbers.txt"));

        try {
            for (int i = 0; i < 100000; i++) {
                names[i] = nameReader.readLine();
                dates[i] = Long.parseLong(numReader.readLine());
                // nameReader.close();
                // numReader.close();
            }
        } catch (FileNotFoundException exc) {
            System.out.println("Oops, no such file here.");
        } catch (IOException exc) {
            System.out.println(exc);
        }
    }

    private static void loadGuessStrings() throws FileNotFoundException {
        BufferedReader strings2Reader = new BufferedReader(new FileReader("sstrings2.txt"));
        BufferedReader strings3Reader = new BufferedReader(new FileReader("sstrings3.txt"));
        BufferedReader strings4Reader = new BufferedReader(new FileReader("sstrings4.txt"));
        try {
            for (int i = 0; i < 10; i++) {
                sstrings2[i] = strings2Reader.readLine();
                sstrings3[i] = strings3Reader.readLine();
                sstrings4[i] = strings4Reader.readLine();
            }
        } catch (FileNotFoundException exc) {
            System.out.println("Oops, no such file here.");
        } catch (IOException exc) {
            System.out.println(exc);
        }
    }
}
