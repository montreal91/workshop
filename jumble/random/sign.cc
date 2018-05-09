
#include <cassert>
#include <cfloat>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

float Fun1( float x ) {
    return -x + 5;
}

float Fun2( float x ) {
    return x + 1;
}

float Fun3( float x ) {
    return x * x - 400;
}

float Fun4( float x ) {
    return 2 * x - 10;
}

typedef pair<float, float> Interval_t;
typedef function<float(float)> RealFunction_t;

bool GetSign( const RealFunction_t& fun, float point ) {
    return fun( point ) == fabs( fun( point ) );
}

Interval_t GetSignChangeInterval( const RealFunction_t& fun ) {
    float start = 0.0f;
    float finish = 0.0f;
    float step = 1.0f;
    float increment = 1.0f;
    do {
        start = finish;
        finish += step * increment;
        increment++;
        if ( finish >= 1000000 ) {
            throw runtime_error( "No sign change." );
        }
    } while ( GetSign( fun, start ) == GetSign( fun, finish ) );
    return Interval_t( start, finish );
}

float GetZero( const RealFunction_t& fun, const Interval_t& ivt ) {
    float start = ivt.first;
    float finish = ivt.second;
    assert( GetSign(fun, start) != GetSign(fun, finish));
    float middle = 0.0f;
    if ( fun( start ) > fun( finish ) ) {
        do {
            middle = ( start + finish ) / 2;
            if ( fun( middle ) >= 0.0f ) {
                start = middle;
            } else {
                finish = middle;
            }
        } while ( fabs( finish - start ) / 2 > 0.01f );
    } else {
        do {
            middle = ( start + finish ) / 2;
            if ( fun( middle ) >= 0.0f ) {
                finish = middle;
            } else {
                start = middle;
            }
        } while ( fabs( finish - start ) / 2 > 0.01f );
    }
    return middle;
}

int main( int argc, char const *argv[] ) {
    cout << GetSign( Fun1, 0 ) << endl;
    cout << GetSign( Fun2, 0 ) << endl;
    cout << GetSign( Fun3, 0 ) << endl;

    cout << endl << FLT_MAX / 2.0 << endl;
    try {
        Interval_t i = GetSignChangeInterval(Fun1);
        cout << i.first << " " << i.second << endl;
        cout << GetZero( Fun1, i ) << endl;
    } catch(exception& e) {
        cout << "A mathenatical error occured.\n";
    }

    try {
        Interval_t i = GetSignChangeInterval(Fun2);
        cout << i.first << " " << i.second << endl;
        cout << GetZero( Fun2, i ) << endl;
    } catch(exception& e) {
        cout << "A mathenatical error occured.\n";
    }

    try {
        Interval_t i = GetSignChangeInterval(Fun3);
        cout << i.first << " " << i.second << endl;
        cout << GetZero( Fun3, i ) << endl;
    } catch(exception& e) {
        cout << "A mathenatical error occured.\n";
    }

    try {
        Interval_t i = GetSignChangeInterval(Fun4);
        cout << i.first << " " << i.second << endl;
        cout << GetZero( Fun4, i ) << endl;
    } catch(exception& e) {
        cout << "A mathenatical error occured.\n";
    }
    return 0;
}
