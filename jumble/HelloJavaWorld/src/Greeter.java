/**
 * Created by montreal on 11/19/15.
 */

public class Greeter {
    private String greetings;

    Greeter() {
        this.greetings = "Hello, World";
    }

    Greeter( String greetings ) {
        this.greetings = "Hello " + greetings;
    }

    public void ToGreet() {
        System.out.printf( "%s%n", this.greetings );
    }
}

