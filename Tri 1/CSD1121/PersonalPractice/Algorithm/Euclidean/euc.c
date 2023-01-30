#include <stdio.h>
#include "euc.h"
int euclidean_Algorithm(int dividend,int divisor)
{
    int remainder;
    do
    {
        remainder = dividend%divisor;
        dividend = divisor;
        divisor = remainder;
    }
    while(remainder != 0);
    return dividend;
}