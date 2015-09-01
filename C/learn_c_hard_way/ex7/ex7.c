
#include <stdio.h>

int main( int argc, char* argv[] ) {
    int bugs = 100;
    double bug_rate = 1.2d;

    printf( "You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate );

    long universe_of_defects = 1L * 1024L * 1024L * 2048L;
    printf( "The entire universe has %ld bugs.\n", universe_of_defects );

    double expected_bugs = bugs * bug_rate;
    printf( "You are expected to have %f bugs.\n", expected_bugs );

    char nul_byte = "\0";
    int care_percentage = bugs * nul_byte;
    printf( "Which means you should care %d%%.\n", care_percentage );

    return 0;
}