
#include <stdio.h>
#include "calc_mean.h"

int main(int argc, char const *argv[])
{
    double v1, v2, m;
    v1 = 101;
    v2 = 22.4;

    m = mean( v1, v2 );

    printf("The mean of %3.2f and %3.2f is %3.2f\n", v1, v2, m );
    
    return 0;
}