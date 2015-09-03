
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char* name;
    int age;
    int height;
    int weight;
};

struct Person* create_person( char* name, int age, int height, int weight ) {
    struct Person* who = malloc( sizeof( struct Person ) );
    assert( who != NULL );

    who->name   = strdup( name );
    who->age    = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void destroy_person( struct Person* who ) {
    assert( who != NULL );

    free( who->name );
    free( who );
}

void print_person( struct Person* who ) {
    assert( who != NULL );

    printf( "Name: %s\n", who->name );
    printf( "\tAge:     %d\n", who->age );
    printf( "\tHeight:  %d\n", who->height );
    printf( "\tWeight:  %d\n", who->weight );
}

int main( int argc, char* argv[] ) {
    struct Person* frodo    = create_person( "Frodo Baggins", 32, 64, 140 );
    struct Person* sam      = create_person( "Samwise Gamgee", 20, 72, 180 );

    printf( "Frodo is at memory location %p:\n", frodo );
    print_person( frodo );

    printf( "Sam is at memory location %p:\n", sam );
    print_person( sam );

    frodo->age += 20;
    frodo->height = 100;
    print_person( frodo );

    // Kill them, kill them both!
    destroy_person( frodo );
    destroy_person( sam );

    return 0;
}
