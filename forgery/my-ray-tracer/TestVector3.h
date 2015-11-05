
#include "Vector3.h"

#include <cxxtest/TestSuite.h>


class Vector3Test : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        Vector3 vec = Vector3();
        TS_ASSERT_EQUALS( vec.x, 0 );
        TS_ASSERT_EQUALS( vec.y, 0 );
        TS_ASSERT_EQUALS( vec.z, 0 );
    }

    void testOneArgumentConstructor() {
        Vector3 vec = Vector3( 3.22 );
        TS_ASSERT_EQUALS( vec.x, 3.22 );
        TS_ASSERT_EQUALS( vec.y, 3.22 );
        TS_ASSERT_EQUALS( vec.z, 3.22 );
    }

    void testThreeArgumentsConstructor() {
        Vector3 vec = Vector3( 4.645, -2* 11.2, 0.009 );
        TS_ASSERT_EQUALS( vec.x, 4.645 );
        TS_ASSERT_EQUALS( vec.y, -22.4 );
        TS_ASSERT_EQUALS( vec.z, 0.009 );
    }

    void testCopyingConstructor() {
        Vector3 vec = Vector3( 2.21, 0.85, 5.06 );
        TS_ASSERT_EQUALS( vec.x, 2.21 );
        TS_ASSERT_EQUALS( vec.y, 0.85 );
        TS_ASSERT_EQUALS( vec.z, 5.06 );
        Vector3 vex = Vector3( vec );
        TS_ASSERT_EQUALS( vex.x, vec.x );
        TS_ASSERT_EQUALS( vex.x, 2.21 );
        TS_ASSERT_EQUALS( vex.y, vec.y );
        TS_ASSERT_EQUALS( vex.y, 0.85 );
        TS_ASSERT_EQUALS( vex.z, vec.z );
        TS_ASSERT_EQUALS( vex.z, 5.06 );
    }

    void testFromVector2Constructor() {
        Vector2 vec2 = Vector2( 4.32, -1.01 );
        TS_ASSERT_EQUALS( vec2.x, 4.32 );
        TS_ASSERT_EQUALS( vec2.y, -1.01 );

        Vector3 vec3 = Vector3( vec2 );
        TS_ASSERT_EQUALS( vec3.x, vec2.x );
        TS_ASSERT_EQUALS( vec3.x, 4.32 );
        TS_ASSERT_EQUALS( vec3.y, vec2.y );
        TS_ASSERT_EQUALS( vec3.y, -1.01 );
        TS_ASSERT_EQUALS( vec3.z, 0 );
    }

    void testOperatorPlus() {
        Vector3 vec     = Vector3( 3.31, 8.68, 2.55 );
        Vector3 vex     = Vector3( 8.68, 3.31, 2.45 );
        Vector3 res1    = vec + vex;
        TS_ASSERT_DELTA( res1.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( res1.y, 11.99, 0.01 );
        TS_ASSERT_DELTA( res1.z, 5.00, 0.01 );


        Vector3 res2    = vex + vec;
        TS_ASSERT_DELTA( res2.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( res2.y, 11.99, 0.01 );
        TS_ASSERT_DELTA( res2.z, 5.00, 0.01 );

        TS_ASSERT_EQUALS( vec.x, 3.31 );
        TS_ASSERT_EQUALS( vec.y, 8.68 );
        TS_ASSERT_EQUALS( vec.z, 2.55 );

        TS_ASSERT_EQUALS( vex.x, 8.68 );
        TS_ASSERT_EQUALS( vex.y, 3.31 );
        TS_ASSERT_EQUALS( vex.z, 2.45 );
    }

    void testOperatorMinus() {
        Vector3 vec     = Vector3( 2.31, 1.23, 4.56 );
        Vector3 vex     = Vector3( 1.21, 2.34, 6.54 );
        Vector3 res1    = vec - vex;
        TS_ASSERT_DELTA( res1.x, 1.10, 0.01 );
        TS_ASSERT_DELTA( res1.y, -1.11, 0.01 );
        TS_ASSERT_DELTA( res1.z, -1.98, 0.01 );

        Vector3 res2    = vex - vec;
        TS_ASSERT_DELTA( res2.x, -1.10, 0.01 );
        TS_ASSERT_DELTA( res2.y, 1.11, 0.01 );
        TS_ASSERT_DELTA( res2.z, 1.98, 0.01 );

        TS_ASSERT_EQUALS( vec.x, 2.31 );
        TS_ASSERT_EQUALS( vec.y, 1.23 );
        TS_ASSERT_EQUALS( vec.z, 4.56 );

        TS_ASSERT_EQUALS( vex.x, 1.21 );
        TS_ASSERT_EQUALS( vex.y, 2.34 );
        TS_ASSERT_EQUALS( vex.z, 6.54 );
    }

    void testOperatorMultiplicate() {
        Vector3 vec     = Vector3( 1.11, 2.22, 3.33 );
        double  alpha   = 4.04;

        Vector3 res1    = vec * alpha;
        TS_ASSERT_DELTA( res1.x, 4.4844, 0.00001 );
        TS_ASSERT_DELTA( res1.y, 8.9688, 0.00001 );
        TS_ASSERT_DELTA( res1.z, 13.4532, 0.00001 );

        TS_ASSERT_EQUALS( vec.x, 1.11 );
        TS_ASSERT_EQUALS( vec.y, 2.22 );
        TS_ASSERT_EQUALS( vec.z, 3.33 );
    }

    void testOperatorPlusEqual() {
        Vector3 vec     = Vector3( 3.31, 8.68, 2.99 );
        Vector3 vex     = Vector3( 8.68, 3.31, 9.92 );
        vec += vex;

        TS_ASSERT_DELTA( vec.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( vec.y, 11.99, 0.01 );
        TS_ASSERT_DELTA( vec.z, 12.91, 0.01 );

        TS_ASSERT_EQUALS( vex.x, 8.68 );
        TS_ASSERT_EQUALS( vex.y, 3.31 );
        TS_ASSERT_EQUALS( vex.z, 9.92 );

        vex += vec;
        TS_ASSERT_DELTA( vex.x, 20.67, 0.01 );
        TS_ASSERT_DELTA( vex.y, 15.30, 0.01 );
        TS_ASSERT_DELTA( vex.z, 22.83, 0.01 );

        TS_ASSERT_DELTA( vec.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( vec.y, 11.99, 0.01 );
        TS_ASSERT_DELTA( vec.z, 12.91, 0.01 );
    }

    void testOperatorMinusEqual() {
        Vector3 vec     = Vector3( 3.31, 8.68, 0.07 );
        Vector3 vex     = Vector3( 8.68, 3.31, -3.02 );
        vec -= vex;

        TS_ASSERT_DELTA( vec.x, -5.37, 0.01 );
        TS_ASSERT_DELTA( vec.y, 5.37, 0.01 );
        TS_ASSERT_DELTA( vec.z, 3.09, 0.01  );

        TS_ASSERT_EQUALS( vex.x, 8.68 );
        TS_ASSERT_EQUALS( vex.y, 3.31 );
        TS_ASSERT_EQUALS( vex.z, -3.02 );

        vex -= vec;
        TS_ASSERT_DELTA( vex.x, 14.05, 0.01 );
        TS_ASSERT_DELTA( vex.y, -2.06, 0.01 );
        TS_ASSERT_DELTA( vex.z, -6.11, 0.01 );


        TS_ASSERT_DELTA( vec.x, -5.37, 0.01 );
        TS_ASSERT_DELTA( vec.y, 5.37, 0.01 );
        TS_ASSERT_DELTA( vec.z, 3.09, 0.01  );
    }

    void testOperatorMultiplicateEqual() {
        Vector3 vec     = Vector3( 3.31, 8.68, -5.37 );
        double alpha    = 0.1;
        vec *= alpha;

        TS_ASSERT_DELTA( vec.x, 0.331, 0.001 );
        TS_ASSERT_DELTA( vec.y, 0.868, 0.001 );
        TS_ASSERT_DELTA( vec.z, -0.537, 0.001 );
        TS_ASSERT_DELTA( alpha, 0.1, 0.001 );
    }

    void testOperatorEquals() {
        Vector3 vec     = Vector3( 3.31, 8.68, -5.01 );

        TS_ASSERT( vec == Vector3( vec ) );
        TS_ASSERT( !( vec == Vector3( 3.31 ) ) );
        TS_ASSERT( !( vec == Vector3( 8.68 ) ) );
        TS_ASSERT( !( vec == Vector3( -5.01 ) ) );
        TS_ASSERT( !( vec == Vector3( 3.31, 8.68, 0 ) ) );
        TS_ASSERT( !( vec == Vector3( 0, 8.68, -5.01 ) ) );
        TS_ASSERT( !( vec == Vector3( 3.31, 0, -5.01 ) ) );
        TS_ASSERT( !( vec == Vector3() ) );
    }

    void testOperatorNotEquals() {
        Vector3 vec     = Vector3( 1, 2, -3 );

        TS_ASSERT( vec != Vector3() );
        TS_ASSERT( vec != Vector3( 1 ) );
        TS_ASSERT( vec != Vector3( 2 ) );
        TS_ASSERT( vec != Vector3( -3 ) );
        TS_ASSERT( vec != Vector3( 1, 2, 0 ) );
        TS_ASSERT( vec != Vector3( 1, 0, -3 ) );
        TS_ASSERT( vec != Vector3( 0, 2, -3 ) );
        TS_ASSERT( !( vec != Vector3( vec ) ) );
    }

    void testDotProduct() {
        Vector3 vec     = Vector3( 0, 3, -3 );
        Vector3 vez     = Vector3( -5, 0, 9 );

        double res1     = vec.DotProduct( vez );
        double res2     = vez.DotProduct( vec );
        double res3     = vec.DotProduct( vec );
        double res4     = vez.DotProduct( vez );

        TS_ASSERT_DELTA( res1, -27, 0.001 );
        TS_ASSERT_DELTA( res2, -27, 0.001 );
        TS_ASSERT_DELTA( res3, 18, 0.001 );
        TS_ASSERT_DELTA( res4, 106, 0.001 );

        TS_ASSERT( vec == Vector3( 0, 3, -3 ) );
        TS_ASSERT( vez == Vector3( -5, 0, 9 ) );
    }

    void testCrossProduct() {
        Vector3 vec     = Vector3( 0.33, -5, 0 );
        Vector3 vex     = Vector3( 0, 4.03, 7 );

        Vector3 res1    = vec.CrossProduct( vex );
        Vector3 res2    = vex.CrossProduct( vec );
        Vector3 res3    = vec.CrossProduct( vec );
        Vector3 res4    = vex.CrossProduct( vex );

        TS_ASSERT_DELTA( res1.x, -35, 0.01 );
        TS_ASSERT_DELTA( res1.y, 2.31, 0.01 );
        TS_ASSERT_DELTA( res1.z, 1.33, 0.01 );

        TS_ASSERT_DELTA( res2.x, 35, 0.01 );
        TS_ASSERT_DELTA( res2.y, -2.31, 0.01 );
        TS_ASSERT_DELTA( res2.z, -1.33, 0.01 );

        TS_ASSERT_DELTA( res3.x, 0, 0.01 );
        TS_ASSERT_DELTA( res3.y, 0, 0.01 );
        TS_ASSERT_DELTA( res3.z, 0, 0.01 );

        TS_ASSERT_DELTA( res4.x, 0, 0.01 );
        TS_ASSERT_DELTA( res4.y, 0, 0.01 );
        TS_ASSERT_DELTA( res4.z, 0, 0.01 );

        TS_ASSERT( vec == Vector3( 0.33, -5, 0 ) );
        TS_ASSERT( vex == Vector3( 0, 4.03, 7 ) );
    }

};
