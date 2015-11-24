
#include <iostream>
#include <functional>

using namespace std;

double eval( function<double(double, double)> f, double x, double y ) {
    return f( x, y );
}

double foo( double x, double y ) {
    return x + y;
}

double foofoo( double x, double y ) {
    return x * y;
}

int main(int argc, char const *argv[]) {
    for ( int i=0; i<5; i++ ) {
        cout << eval( foo, i, i ) << " ";
    }
    cout << endl;

    for ( int i=0; i<5; i++ ) {
        cout << eval( foofoo, i, i ) << " ";
    }
    cout << endl;
    return 0;
}
