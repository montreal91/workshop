
#include "folded-greeter.h"

FoldedGreeter::FoldedGreeter( const int x ) {
    this->x = x;
}

FoldedGreeter::~FoldedGreeter() {
}

void
FoldedGreeter::PrintSingleGreetings() const {
    std::cout << "Hello, guys!" << std::endl;
}

void
FoldedGreeter::PrintMultipleGreetings() const {
    for ( int i = 0; i < x; i++ ) {
        std::cout << "Hello, guys!" << std::endl;
    }
}
