
#include <stdio.h>

int main( int argc, char* argv[] ) {
    for ( int i = 1; i < argc; i++ ) {
        printf( "arg %d: %s\n", i, argv[ i ] );
    }

    char* states[] = {
        "California",
        "Colorado",
        "Ohio",
        "Oregon",
        "Washington",
        "Texas",
    };
    int num_states = 7;
    for ( int i=0; i < num_states; i++ ) {
        printf( "State %d: %s\n", i, states[ i ] );
    }
    return 0;
}
