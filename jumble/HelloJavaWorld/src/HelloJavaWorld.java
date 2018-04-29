/**
 * Created by montreal on 11/19/15.
 */

public class HelloJavaWorld {
    public static void main( String args[] ) {
        Word v = new Word();
//         String s = v.scramble("Udacity");
//        String s = v.getWordWithSwappedLetters("Udacity", 2, 5);
        String s = v.printSubstrings("Udacity");
        System.out.println(s);
    }
}
