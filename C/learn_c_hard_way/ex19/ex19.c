
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ex19.h"


int
MonsterAttack( void* self, int damage ) {
    Monster_t* monster = self;

    printf( "You attack %s!", monster->_( description ) );

    monster->hit_points -= damage;

    if( monster->hit_points > 0 ) {
        printf( "It is still alive.\n" );
        return 0;
    } else {
        printf( "It is dead! \n" );
        return 1;
    }
}

int 
MonsterInit( void* self ) {
    Monster_t* monster  = self;
    monster->hit_points = 10;
    return 1;
}

Object_t Monster_tProto = {
    .init   = MonsterInit,
    .attack = MonsterAttack
};

void*
RoomMove( void* self, Direction_t direction ) {
    Room_t* room = self;
    Room_t* next = NULL;

    if ( direction == NORTH && room->north ) {
        printf( "You go north, into:\n" );
        next = room->north;
    } else if ( direction == SOUTH && room->south ) {
        printf( "You go south, into:\n" );
        next = room->south;
    } else if ( direction == EAST && room->east ) {
        printf( "You go east, into:\n" );
        next = room->east;
    } else if ( direction == WEST && room->west ) {
        printf( "You go west, into:\n" );
        next = room->west;
    } else {
        printf( "You can't go that direction." );
        next = NULL;
    }

    if ( next ) {
        next->_( describe )( next );
    }
    return next;
}


int
RoomAttack( void* self, int damage ) {
    Room_t* room        = self;
    Monster_t* monster  = room->bad_guy;

    if ( monster ) {
        monster->_( attack )( monster, damage );
        return 1;
    } else {
        printf( "You flail in the air at nothing. Idiot.\n" );
        return 0;
    }
}

Object_t Room_tProto = {
    .move   = RoomMove,
    .attack = RoomAttack,
};

void*
MapMove( void* self, Direction_t direction ) {
    Map_t* map          = self;
    Room_t* location    = map->location;
    Room_t* next        = NULL;

    next                = location->_( move )( location, direction );

    if ( next ) {
        map->location = next;
    }
    return next;
}

int
MapAttack( void* self, int damage ) {
    Map_t* map          = self;
    Room_t* location    = map->location;

    return location->_( attack )( location, damage );
}

int
MapInit( void* self ) {
    Map_t* map      = self;

    // Make some rooms for a small map
    Room_t* hall    = NEW( Room_t, "The great Hall" );
    Room_t* throne  = NEW( Room_t, "The throne room" );
    Room_t* arena   = NEW( Room_t, "The arena with the minotaur" );
    Room_t* kitchen = NEW( Room_t, "Kitchen, you have the knife now" );

    // Put the bad guy in the arena
    arena->bad_guy  = NEW( Monster_t, "The evil minotaur" );

    // Setup the map rooms
    hall->north     = throne;

    throne->west    = arena;
    throne->east    = kitchen;
    throne->south   = hall;

    arena->east     = throne;
    kitchen->west   = throne;

    // Start the map and the character off in the hall
    map->start      = hall;
    map->location   = hall;

    return 1;
}

Object_t Map_tProto = {
    .init   = MapInit,
    .move   = MapMove,
    .attack = MapAttack,
};

int
ProcessInput( Map_t* game ) {
    printf( "\n> " );

    char ch     = getchar();
    getchar();

    int damage  = rand() % 4;

    if ( ch == -1 ) {
        printf( "Giving up? You suck.\n" );
        return 0;
    } else if ( ch == 'n' ) {
        game->_( move )( game, NORTH );
    } else if ( ch == 's' ) {
        game->_( move )( game, SOUTH );
    } else if ( ch == 'e' ) {
        game->_( move )( game, EAST );
    } else if ( ch == 'w' ) {
        game->_( move )( game, WEST );
    } else if ( ch == 'a' ) {
        game->_( attack )( game, damage );
    } else if ( ch == 'l' ) {
        printf( "You can go:\n" );
        if ( game->location->north ) {
            printf( "NORTH\n" );
        }
        if ( game->location->south ) {
            printf( "SOUTH\n" );
        }
        if ( game->location->east ) {
            printf( "EAST\n" );
        }
        if ( game->location->west ) {
            printf( "WEST\n" );
        }
    } else {
        printf( "What the fuck?: %d\n", ch );
    }
    return 1;
}

int
main( int argc, char** argv ) {
    srand( time( NULL ) );

    Map_t* game = NEW( Map_t, "The Hall of the Minotaur." );

    printf( "You enter the " );
    game->location->_( describe )( game->location );

    while( ProcessInput( game ) ) {
    }

    return 0;
}
