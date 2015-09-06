
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

void
ObjectDestroy( void* self ) {
    Object_t* obj = self;
    if ( obj ) {
        if ( obj->description ) {
            free( obj->description );
        }
        free( obj );
    }
}

void
ObjectDescribe( void* self ) {
    Object_t* obj = self;
    printf( "%s.\n", obj->description );
}

int
ObjectInit( void* self ) {
    return 1;
}

void*
ObjectMove( void* self, Direction_t direction ) {
    printf( "You can't go that direction.\n" );
    return NULL;
}

int
ObjectAttack( void* self, int damage ) {
    printf( "You can't attack that.\n" );
    return 0;
}

void*
ObjectNew( size_t size, Object_t proto, char* description ) {
    if ( !proto.init ) {
        proto.init = ObjectInit;
    }
    if ( !proto.describe ) {
        proto.describe = ObjectDescribe;
    }
    if ( !proto.destroy ) {
        proto.destroy = ObjectDestroy;
    }
    if ( !proto.attack ) {
        proto.attack = ObjectAttack;
    }
    if ( !proto.move ) {
        proto.move = ObjectMove;
    }

    Object_t *el    = calloc( 1, size );
    *el             = proto;

    el->description = strdup( description );

    // Initalize it with whatever init we were given
    if ( !el->init( el ) ) {
        // Looks like it didn't initalize properly
        el->destroy( el );
        return NULL;
    } else {
        // All done, we made an object of any type
        return el;
    }
}
