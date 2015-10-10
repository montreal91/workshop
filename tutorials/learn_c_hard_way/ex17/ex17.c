
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[ MAX_DATA ];
    char email[ MAX_DATA ];
};

struct Database {
    struct Address rows[ MAX_ROWS ];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void
Die( const char* message ) {
    if ( errno ) {
        perror( message );
    } else {
        printf( "ERROR: %s\n", message );
    }
    exit( 1 );
}

void
PrintAddress( struct Address* addr ) {
    printf( "%d %s %s\n", addr->id, addr->name, addr->email );
}

void
LoadDatabase( struct Connection* conn ) {
    int rc = fread( conn->db, sizeof( struct Database ), 1, conn->file );
    if ( rc != 1 ) {
        Die( "Failed to load database." );
    }
}

struct Connection*
OpenDatabase( const char* filename, char mode ) {
    struct Connection *conn = malloc( sizeof( struct Connection ) );
    if ( !conn ) {
        Die( "Memory error" );
    }
    conn->db = malloc( sizeof( struct Database ) );
    if ( !conn->db ) {
        Die( "Memory error." );
    }
    if ( mode == 'c' ) {
        conn->file = fopen( filename, "w" );
    } else {
        conn->file = fopen( filename, "r+" );
        if ( conn->file ) {
            LoadDatabase( conn );
        }
    }
    if ( !conn->file ) {
        Die( "Failed to open the file." );
    }
    return conn;
}

void 
CloseDatabase( struct Connection* conn ) {
    if ( conn ) {
        if ( conn->file ) {
            fclose( conn->file );
        }
        if ( conn->db ) {
            free( conn->db );
        }
        free( conn );
    }
}

void 
WriteDatabase( struct Connection* conn ) {
    rewind( conn->file );

    int rc = fwrite( conn->db, sizeof( struct Database ), 1, conn->file );
    if ( rc != 1 ) {
        Die( "Failed to write database." );
    }

    rc = fflush( conn->file );
    if ( rc == -1 ) {
        Die( "Cannot flush database." );
    }
}

void 
CreateDatabase( struct Connection* conn ) {
    for ( int i=0; i<MAX_ROWS; i++ ) {
        struct Address addr = { .id = i, .set = 0 };
        conn->db->rows[ i ] = addr;
    }
}

void
SetDatabase( struct Connection* conn, int id, const char* name, const char* email ) {
    struct Address* addr = &conn->db->rows[ id ];
    if ( addr->set ) {
        Die( "Already set, delete it first" );
    }

    addr->set = 1;

    char* res = strncpy( addr->name, name, MAX_DATA );

    if ( !res ) {
        Die( "Name copy failed." );
    }

    res = strncpy( addr->email, email, MAX_DATA );
    if ( !res ) {
        Die( "Email copy failed." );
    }
}

void 
GetDatabase( struct Connection* conn, int id ) {
    struct Address* addr = &conn->db->rows[ id ];

    if ( addr->set ) {
        PrintAddress( addr );
    } else {
        Die( "ID is not set." );
    }
}

void
DeleteDatabase( struct Connection* conn, int id ) {
    struct Address addr = { .id = id, .set = 0 };
    conn->db->rows[ id ] = addr;
}

void
ListDatabase( struct Connection* conn ) {
    struct Database* db = conn->db;

    for ( int i=0; i<MAX_ROWS; i++ ) {
        struct Address* cur = &db->rows[ i ];

        if ( cur->set ) {
            PrintAddress( cur );
        }
    }
}

int
main( int argc, char* argv[] ) {
    if ( argc < 3 ) {
        Die( "USAGE: ex17 <dbfile> <action> [action params]" );
    }

    char* filename = argv[ 1 ];
    char action = argv[ 2 ][ 0 ];
    struct Connection* conn = OpenDatabase( filename, action );
    int id = 0;

    if ( argc > 3 ) {
        id = atoi( argv[ 3 ] );
    }
    if ( id>= MAX_ROWS ) {
        Die( "There is not that many records." );
    }

    if ( action == 'c' ) {
        CreateDatabase( conn );
        WriteDatabase( conn );
    } else if ( action == 'g' ) {
        if ( argc != 4 ) {
            Die( "Need an id to get" );
        } else {
            GetDatabase( conn, id );
        }
    } else if ( action == 's' ) {
        if ( argc != 6 ) {
            Die( "Need id, name, email to set" );
        } else {
            SetDatabase( conn, id, argv[ 4 ], argv[ 5 ] );
            WriteDatabase( conn );
        }
    } else if ( action == 'd' ) {
        if ( argc != 4 ) {
            Die( "Need id to delete" );
        } else {
            DeleteDatabase( conn, id );
            WriteDatabase( conn );
        }
    } else if ( action == 'l' ) {
        ListDatabase( conn );
    } else {
        Die( "Invalid action, only: c=create, g=get, d=delete, l=list" );
    }
    CloseDatabase( conn );
    return 0;
}
