#include <stdio.h>
#include "fib.h"
#include <math.h>

int main(void)
{
    int value;
    while (1 == scanf("%d",&value))
    {
        if (value <0)
        {
            continue;
        }
        fibonacci(value);
    }
}