
#ifndef __FOLDED_GREETER_H__
#define __FOLDED_GREETER_H__

#include <iostream>

class FoldedGreeter {
public:
    FoldedGreeter( const int x );
    ~FoldedGreeter();

    void PrintSingleGreetings() const;
    void PrintMultipleGreetings() const;

private:
    int x;
};

#endif