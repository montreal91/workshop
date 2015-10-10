
public class MyName {
    private String first_name;
    private String last_name;

    public MyName( ){
        this.first_name     = "Random";
        this.last_name      = "Dude";
    }

    public MyName( String first_name, String last_name ){
        this.first_name     = first_name;
        this.last_name      = last_name;
    }

    public String GetFirstName( ){
        return this.first_name;
    }

    public String GetLastName( ){
        return this.last_name;
    }

    public String GetShortedName( ){
        return this.first_name.substring( 0, 1 ) + ". " + this.last_name;
    }

    public String GetFullName( ){
        return this.first_name + " " + this.last_name;
    }
}
