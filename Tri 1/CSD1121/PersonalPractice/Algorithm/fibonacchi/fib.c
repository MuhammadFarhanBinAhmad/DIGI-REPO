#include <stdio.h>
#include "fib.h"
#include <math.h>

    int a = 0;
    int old_a=0;
    int b =1;
    double sum;

void fibonacci(int value)
{
    /*for (int i = 0; i <= value; i++)
    {
        old_a = a;
        a = b;
        b += old_a;
        sum = pow(2.f,(double)b);
        printf("%.0f\n",sum);
    }*/
    //recursion
    if (value <= 1)
    {
        return value;
    }
    return value = (value - 1) + (value - 2);
    //dynamic programming
    int a[2];
    a[0] = 0;
    a[1] = 1;
    int sum;
    for (int i = 2; i < value; i++)
    {
        sum = a[i - 1] + a[i - 2];
    }
    return sum;
}