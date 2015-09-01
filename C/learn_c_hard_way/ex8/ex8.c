
#include <stdio.h>

int main( int argc, char* argv[] ) {
    int areas[]         = { 10, 12, 13, 14, 443 };
    char name[]         = "Alex";
    char full_name[]    = { 'A', 'l', 'e', 'x', ' ', 'C', 'o', 'd', 'y', '\0' };
    printf( "The size of an int: %ld\n", sizeof( int ) );
    printf( "The size of areas (int[]): %ld\n", sizeof( areas ) );
    printf( "The number of ints in areas: %ld\n", sizeof( areas ) / sizeof( int ) );
    printf( "The first area is %d, the second area is %d.\n", areas[ 0 ], areas[ 1 ] );
    printf( "The size of a char: %ld.\n", sizeof( char ) );
    printf( "The size of name (char[]): %ld.\n", sizeof( name ) );
    printf( "The size of full name (char[]): %ld.\n", sizeof( full_name ) );
    printf( "name=\"%s\" and full_name=\"%s\"\n.", name, full_name );

    return 0;
}
