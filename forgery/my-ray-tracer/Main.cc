
#include "Vector2.h"
#include "Vector3.h"
#include "Ray.h"

#include <iostream>

using namespace std;

int
main( int argc, char const *argv[] ) {
    Vector3 a = Vector3( 1, 0, 0 );
    Vector3 b = Vector3( 0, 1, 0 );
    Vector3 c = Vector3( 0, 0, 1 );

    Vector3 o = Vector3( 0, 0, 0 );
    Vector3 d = Vector3( 1, 0, 0 );

    Triangle abc;
    abc.vert0 = a;
    abc.vert1 = b;
    abc.vert2 = c;

    Ray ray = Ray( o, d );

    Point3_t* inter = new Point3_t();
    int res = ray.GetIntersectionWithTriangle( abc, inter );

    if ( res == Ray::SUCCESS ) { 
        cout << "Fuck Yeah!\n";
        cout << "x: " << inter->x << endl;
        cout << "y: " << inter->y << endl;
        cout << "z: " << inter->z << endl;
    } else if ( res == Ray::FAIL ) {
        cout << "Fuck No!\n"; 
    }
    delete inter;
    return 0;
}
