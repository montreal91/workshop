
#ifndef __GREETER_H__
#define __GREETER_H__

#include <iostream>

class Greeter {
public:
    Greeter( const int x );
    ~Greeter();

    void PrintSingleGreetings() const;
    void PrintMultipleGreetings() const;

private:
    int x;
};

#endif