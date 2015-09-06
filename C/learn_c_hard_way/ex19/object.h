
#ifndef __OBJECT_H__
#define __OBJECT_H__


typedef enum {
    NORTH, SOUTH, EAST, WEST,
} Direction_t;


typedef struct {
    char*   description;
    int     ( *init )( void* self );
    void    ( *describe )( void* self );
    void    ( *destroy )( void* self );
    void*   ( *move )( void* self, Direction_t direction );
    int     ( *attack )( void* self, int damage );
} Object_t;


int     ObjectInit( void* self );
void    ObjectDestroy( void* self );
void    ObjectDescribe( void* self );
void*   ObjectMove( void* self, Direction_t direction );
int     ObjectAttack( void* self, int damage );
void*   ObjectNew( size_t size, Object_t proto, char* description );


#define NEW( T, N ) ObjectNew( sizeof( T ), T##Proto, N )
#define _( N ) proto.N


#endif
