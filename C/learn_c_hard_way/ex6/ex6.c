
#include <stdio.h>

int main( int argc, char* argv[] ) {
    int distance = 9000;
    float power = 987.65f;
    double super_power = 1245.3423d;
    char initial = "Y";
    char first_name[] = "Alex";
    char last_name[] = "Kinley";

    printf( "You are over %d miles away.\n", distance );
    printf( "You have %f levels of power. \n", power );
    printf( "You have %f awesome super powers. \n", super_power );
    printf( "\tI have an initial %c. \n", initial );
    printf( "\tI have a first name %s.\n", first_name );
    printf( "\tI have a last name %s.\n", last_name );
    printf( "My whole name is %s %c. %s.\n", first_name, initial, last_name );

    return 0;
}