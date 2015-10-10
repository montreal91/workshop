
#include <stdio.h>

int main( int argc, char* argv[] ) {
    int ages[]      = { 23, 43, 12, 89, 2 };
    char *names[]   = {
        "Alan", "Frank", "Mary", "John", "Fuck",
    };
    int count       = sizeof( ages ) / sizeof( int );

    printf( "\t-------\n" );
    // Using indexing
    for ( int i=0; i<count; i++ ) {
        printf( "%s has %d years alive.\n", names[ i ], ages[ i ] );
    }

    printf( "\t-------\n" );
    // Using pointers
    int* cur_age    = ages;
    char** cur_name = names;
    for ( int i=0; i<count; i++ ) {
        printf( "%s is %d years old.\n", *( cur_name + i ), *( cur_age + i ) );
    }

    printf( "\t-------\n" );
    // Third way, pointers are just arrays
    for ( int i=0; i<count; i++ ) {
        printf( "%s is %d years old again.\n", cur_name[ i ], cur_age[ i ] );
    }

    printf( "\t-------\n" );
    // Fourth way with pointers in a stupid complex way
    for ( cur_name=names, cur_age=ages; ( cur_age - ages ) < count; cur_name++, cur_age++ ) {
        printf( "%s lived %d years so far.\n", *cur_name, *cur_age );
    }

    return 0;
}
