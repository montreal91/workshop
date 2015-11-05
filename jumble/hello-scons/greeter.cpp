
#include "greeter.h"

Greeter::Greeter( const int x ) {
    this->x = x;
}

Greeter::~Greeter() {
}

void
Greeter::PrintSingleGreetings() const {
    std::cout << "Hello, world! GODDAMNIT!" << std::endl;
}

void
Greeter::PrintMultipleGreetings() const {
    for ( int i = 0; i < x; i++ ) {
        std::cout << "Hello, world! GODDAMNIT!" << std::endl;
    }
}
