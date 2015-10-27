
#include "Application.hpp"

#include <iostream>


int main( int argc, char const *argv[] ) {
    try {
        Application app;
        app.run();
    } catch (std::exception& e ) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}
