#include <stdio.h>
#include "leap_year.h"
int main(void)
{
    int year;
    while ( 1 == scanf("%d",&year))
    {
        if (year <= 0 || year >= 999999)
        {
            continue;
        }
        leap_year(year)?printf("%d is a leap year\n",year):printf("%d is not a leap year\n",year);
    }
    return 0;
}