
#ifndef __EX19_H__
#define __EX19_H__

#include "object.h"

struct Monster {
    Object_t proto;
    int hit_points;
};

typedef struct Monster Monster_t;

int     MonsterAttack( void* self, int damage );
int     MonsterInit( void* self );

struct Room {
    Object_t proto;

    Monster_t* bad_guy;

    struct Room* north;
    struct Room* south;
    struct Room* east;
    struct Room* west;
};

typedef struct Room Room_t;

void*   RoomMove( void* self, Direction_t direction );
int     RoomAttack( void* self, int damage );
int     RoomInit( void* self );

struct Map {
    Object_t proto;
    Room_t* start;
    Room_t* location;
};

typedef struct Map Map_t;

void*   MapMove( void* self, Direction_t direction );
int     MapAttack( void* self, int Damage );
int     MapInit( void* self );

#endif
