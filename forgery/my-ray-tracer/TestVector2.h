
#include "Vector2.h"

#include <cxxtest/TestSuite.h>


class Vector2Test : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        Vector2 vec = Vector2();
        TS_ASSERT_EQUALS( vec.x, 0 );
        TS_ASSERT_EQUALS( vec.y, 0 );
    }

    void testOneArgumentConstructor() {
        Vector2 vec = Vector2( 3.22 );
        TS_ASSERT_EQUALS( vec.x, 3.22 );
        TS_ASSERT_EQUALS( vec.y, 3.22 );
    }

    void testTwoArgumentsConstructor() {
        Vector2 vec = Vector2( 4.645, -2* 11.2 );
        TS_ASSERT_EQUALS( vec.x, 4.645 );
        TS_ASSERT_EQUALS( vec.y, -22.4 );
    }

    void testCopyingConstructor() {
        Vector2 vec = Vector2( 2.21, 0.85 );
        TS_ASSERT_EQUALS( vec.x, 2.21 );
        TS_ASSERT_EQUALS( vec.y, 0.85 );
        Vector2 vex = Vector2( vec );
        TS_ASSERT_EQUALS( vex.x, vec.x );
        TS_ASSERT_EQUALS( vex.x, 2.21 );
        TS_ASSERT_EQUALS( vex.y, vec.y );
        TS_ASSERT_EQUALS( vex.y, 0.85 );
    }

    void testOperatorPlus() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        Vector2 vex     = Vector2( 8.68, 3.31 );
        Vector2 res1    = vec + vex;
        TS_ASSERT_DELTA( res1.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( res1.y, 11.99, 0.01 );

        Vector2 res2    = vex + vec;
        TS_ASSERT_DELTA( res2.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( res2.y, 11.99, 0.01 );
        TS_ASSERT_EQUALS( vec.x, 3.31 );
        TS_ASSERT_EQUALS( vec.y, 8.68 );
        TS_ASSERT_EQUALS( vex.x, 8.68 );
        TS_ASSERT_EQUALS( vex.y, 3.31 );
    }

    void testOperatorMinus() {
        Vector2 vec     = Vector2( 2.31, 1.23 );
        Vector2 vex     = Vector2( 1.21, 2.34 );
        Vector2 res1    = vec - vex;
        TS_ASSERT_DELTA( res1.x, 1.10, 0.01 );
        TS_ASSERT_DELTA( res1.y, -1.11, 0.01 );

        Vector2 res2    = vex - vec;
        TS_ASSERT_DELTA( res2.x, -1.10, 0.01 );
        TS_ASSERT_DELTA( res2.y, 1.11, 0.01 );
        TS_ASSERT_EQUALS( vec.x, 2.31 );
        TS_ASSERT_EQUALS( vec.y, 1.23 );
        TS_ASSERT_EQUALS( vex.x, 1.21 );
        TS_ASSERT_EQUALS( vex.y, 2.34 );
    }

    void testOperatorMultiplicate() {
        Vector2 vec     = Vector2( 1.11, 2.22 );
        double  alpha   = 4.04;
        Vector2 res1    = vec * alpha;
        TS_ASSERT_DELTA( res1.x, 4.4844, 0.00001 );
        TS_ASSERT_DELTA( res1.y, 8.9688, 0.00001 );
        TS_ASSERT_EQUALS( vec.x, 1.11 );
        TS_ASSERT_EQUALS( vec.y, 2.22 );
    }

    void testOperatorPlusEqual() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        Vector2 vex     = Vector2( 8.68, 3.31 );
        vec += vex;
        TS_ASSERT_DELTA( vec.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( vec.y, 11.99, 0.01 );
        TS_ASSERT_EQUALS( vex.x, 8.68 );
        TS_ASSERT_EQUALS( vex.y, 3.31 );

        vex += vec;
        TS_ASSERT_DELTA( vex.x, 20.67, 0.01 );
        TS_ASSERT_DELTA( vex.y, 15.30, 0.01 );
        TS_ASSERT_DELTA( vec.x, 11.99, 0.01 );
        TS_ASSERT_DELTA( vec.y, 11.99, 0.01 );
    }

    void testOperatorMinusEqual() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        Vector2 vex     = Vector2( 8.68, 3.31 );
        vec -= vex;
        TS_ASSERT_DELTA( vec.x, -5.37, 0.01 );
        TS_ASSERT_DELTA( vec.y, 5.37, 0.01 );
        TS_ASSERT_EQUALS( vex.x, 8.68 );
        TS_ASSERT_EQUALS( vex.y, 3.31 );

        vex -= vec;
        TS_ASSERT_DELTA( vex.x, 14.05, 0.01 );
        TS_ASSERT_DELTA( vex.y, -2.06, 0.01 );
        TS_ASSERT_DELTA( vec.x, -5.37, 0.01 );
        TS_ASSERT_DELTA( vec.y, 5.37, 0.01 );
    }

    void testOperatorMultiplicateEqual() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        double alpha    = 0.1;
        vec *= alpha;

        TS_ASSERT_DELTA( vec.x, 0.331, 0.001 );
        TS_ASSERT_DELTA( vec.y, 0.868, 0.001 );
        TS_ASSERT_DELTA( alpha, 0.1, 0.001 );
    }

    void testOperatorEquals() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        Vector2 vex     = Vector2( vec );
        Vector2 vez     = Vector2( 8.68, 3.31 );

        TS_ASSERT( vec == vex );
        TS_ASSERT( !( vec == vez ) );
    }

    void testOperatorNotEquals() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        Vector2 vex     = Vector2( vec );
        Vector2 vez     = Vector2( 8.68, 3.31 );

        TS_ASSERT( !( vec != vex ) );
        TS_ASSERT( vec != vez );
        TS_ASSERT( vec != Vector2( 3.31, 8.88 ) );
        TS_ASSERT( vec != Vector2( 3.33, 8.68 ) );
    }

    void testDotProduct() {
        Vector2 vec     = Vector2( 3.31, 8.68 );
        Vector2 vez     = Vector2( 8.68, 3.31 );

        double res1     = vec.DotProduct( vez );
        double res2     = vez.DotProduct( vec );
        double res3     = vec.DotProduct( vec );

        TS_ASSERT_DELTA( res1, 57.461, 0.001 );
        TS_ASSERT_DELTA( res2, 57.461, 0.001 );
        TS_ASSERT_DELTA( res3, 86.299, 0.001 );
    }
};
