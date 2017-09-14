
public class NaumenTest {
    public static void main(String[] args) {
        String[] names = {
            "kare",
            "kanojo",
            "karetachii",
            "karetachih",
            "karetachig",
            "karetachif",
            "karetachie",
            "karetachid",
            "karetachic",
            "karetachib",
            "karetachia",
            "korosu",
            "sakura",
        };
        long[] times = {
            10,
            20,
            9,
            8,
            7,
            6,
            5,
            4,
            2,
            2,
            2,
            7,
            3,
        };

        ITrieSearcher its = new ITrieSearcher();
        its.refresh(names, times);

        String[] g1 = its.guess("k");
        for (int i = 0; i<g1.length; i++) {
            System.out.println(g1[i]);
        }
        System.out.println(g1.length);

        String[] g2 = its.guess("ka");
        for (int i = 0; i<g2.length; i++) {
            System.out.println(g2[i]);
        }
        System.out.println(g2.length);

        String[] g3 = its.guess("kar");
        for (int i = 0; i<g3.length; i++) {
            System.out.println(g3[i]);
        }
        System.out.println(g3.length);
    }
}
