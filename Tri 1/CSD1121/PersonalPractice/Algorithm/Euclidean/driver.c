#include <stdio.h>
#include "euc.h"

int main(void)
{
    //int dividend=0;
    //int divisor=0;
    /*while(1 == scanf("%d,%d",&dividend,&divisor))
    {
        printf("%d\n",euclidean_Algorithm(dividend,divisor));
    }*/
    printf("%d\n",euclidean_Algorithm(1785,546));
    printf("%d\n",euclidean_Algorithm(2341,122));    
    printf("%d\n",euclidean_Algorithm(17385,123));    
    printf("%d\n",euclidean_Algorithm(2344,22));    
    printf("%d\n",euclidean_Algorithm(1234,12));    
    
    return 0;
}