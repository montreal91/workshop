
#include "greeter.h"
#include "folded-greeter/folded-greeter.h"

#include <SFML/Graphics.hpp>

int 
main( int argc, char const *argv[] ) {

    sf::Time sf_time;

    std::cout << "Kick Ass!\n";

    Greeter greeter = Greeter( 3 );
    FoldedGreeter fd_greeter = FoldedGreeter( 3 );

    greeter.PrintSingleGreetings();
    std::cout << "\n";
    greeter.PrintMultipleGreetings();
    std::cout << "\n";

    fd_greeter.PrintSingleGreetings();
    std::cout << "\n";
    fd_greeter.PrintMultipleGreetings();
    return 0;
}
