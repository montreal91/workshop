
#include <iostream>

template<typename T>
class EvilClass {
public:
    virtual void DoSomething( T param ) {
        std::cout << "I've done something\n";
    }
};

typedef EvilClass<int> EvilInt;

class EvilFloat : public EvilInt {
public:
    virtual void DoSomething( double param ) {
        for ( int i = 0; i < param; i++ ) {
            std::cout << "Int " << i << std::endl;
        }
    }
};

int main( int argc, char const *argv[] ) {
    EvilFloat f;
    f.DoSomething( 3 );
    return 0;
}
