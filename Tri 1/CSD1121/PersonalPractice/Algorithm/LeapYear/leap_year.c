#include <stdio.h>
#include "leap_year.h"
int leap_year(int year)
{
    //if divisible by 400 or is divisible by 4 but not 100, its a leap year
    return (year%400==0 || (year%100 && year%4==0)?1:0);
}