/**
 * Created by montreal on 11/19/15.
 */

public class HelloJavaWorld {
    public static void main( String args[] ) {
        Greeter one = new Greeter();
        Greeter two = new Greeter( "Montreal" );

        System.out.printf( "Hello, Java World%n" );
        one.ToGreet();
        two.ToGreet();
    }
}
