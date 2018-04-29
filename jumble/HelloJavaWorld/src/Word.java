/**
 * Created by montreal on 6/18/16.
 */

import java.util.Random;

public class Word {
    private Random generator = new Random();

    public Word()  //leave the constructor alone
    {
        generator = new Random();
        final long SEED = 42;
        generator.setSeed(SEED);
    }
    /**
     * Gets a version of this word with the leters scrambled
     * @param word the string to scramble
     * @return the scrabled string
     */
    public String scramble(String word) {
        //TODO scramble the letters following the pseudocode
        String res = word;
        // for (int i = 0; i < word.length(); i++) {
        //     System.out.println(this.getRandomInt(0, word.length()));
        // }
        for (int c = 0; c < word.length(); c++) {
            int i = getRandomInt(0, word.length()-2);
            int j = getRandomInt(i+1, word.length()-1);
            // System.out.print(i);
            // System.out.print(j);
            // System.out.print("\n");
            res = getWordWithSwappedLetters(res, i, j);
        }
        return res;
    }

    private int getRandomInt(int start, int finish) {
        // Random rand = new Random();
        return generator.nextInt((finish - start) + 1) + start;
    }

    public String getWordWithSwappedLetters(String word, int i, int j) {
        // System.out.print(i);
        // System.out.print(j);
        // System.out.print("\n");
        String start = word.substring(0, i);
        String at_i = word.substring(i, i+1);
        String between_i_j = word.substring(i+1, j);
        if (j < word.length() - 1) {
            String at_j = word.substring(j, j+1);
            String after_j = word.substring(j+1);
            return start + at_j + between_i_j + at_i + after_j;
        } else {
            String at_j = word.substring(j);
            return start + at_j + between_i_j + at_i;
        }
    }

    public String printSubstrings(String word) {
        String res = "";
        for (int j = 1; j < word.length(); j++) {
            for (int i = 0; i < word.length()-j+1; i++) {
                System.out.println(word.substring(i, i+j));
                res += word.substring(i, i+j);
            }
        }
        res += word;
        return res;
    }
}
