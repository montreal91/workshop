
// #include <vector>
#include <iostream>

#include "mage.h"
#include "society.h"

int main() {
    MSociety socium;
    for ( int i = 0; i < 10; i++ ) {
        MMage m( i % 2 == 0 );
        socium.AddCitizen( m );
    }
    socium.PrintStatistics( std::cout );
    socium.LiveManyYears( 5 );
    socium.PrintStatistics( std::cout );
    char input;
    while ( input != 'q' ) {
        std::cin >> input;
        if ( input == 'n' ) {
            socium.LiveManyYears( 5 );
            socium.PrintStatistics( std::cout );
        }
    }
    return 0;
}
