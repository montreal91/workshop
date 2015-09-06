
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
Die( const char* message ) {
    if ( errno ) {
        perror( message );
    } else {
        printf( "ERROR: %s\n", message );
    }
    exit( 1 );
}

typedef int ( *compare_t )( int a, int b );

int*
BubbleSort( int* numbers, int count, compare_t cmp ) {
    int *target = malloc( count * sizeof( int ) );

    if ( !target ) {
        Die( "Memory error." );
    }

    memcpy( target, numbers, count * sizeof( int ) );

    for ( int i=0; i<count; i++ ) {
        for ( int j=0; j<count-1; j++ ) {
            if ( cmp( target[j], target[j+1] ) > 0 ) {
                int temp        = target[ j+1 ];
                target[ j+1 ]   = target[ j ];
                target[ j ]     = temp;
            }
        }
    }
    return target;
}

int
SortedOrder( int a, int b ) {
    return a - b;
}

int
ReverseOrder( int a, int b ) {
    return b - a;
}

int
StrangeOrder( int a, int b ) {
    if ( a == 0 || b == 0 ) {
        return 0;
    } else {
        return a % b;
    }
}

void
TestSorting( int* numbers, int count, compare_t cmp ) {
    int* sorted = BubbleSort( numbers, count, cmp );
    if ( !sorted ) {
        Die( "Failed to sort as requested." );
    }
    for ( int i=0; i<count; i++ ) {
        printf( "%d ", sorted[ i ] );
    }
    printf( "\n" );

    free( sorted );
}

int
main( int argc, char* argv[] ) {
    if( argc < 2 ) {
        Die( "USAGE: ex18 4 3 1 5 6 0" );
    }
    int count       = argc - 1;
    char** inputs   = argv + 1;

    int* numbers_ptr = malloc( count * sizeof( int ) );
    if ( !numbers_ptr ) {
        Die( "Memory error." );
    }

    for( int i=0; i<count; i++ ) {
        numbers_ptr[ i ] = atoi( inputs[ i ] );
    }
    TestSorting( numbers_ptr, count, SortedOrder );
    TestSorting( numbers_ptr, count, ReverseOrder );
    TestSorting( numbers_ptr, count, StrangeOrder );

    free( numbers_ptr );
    return 0;
}