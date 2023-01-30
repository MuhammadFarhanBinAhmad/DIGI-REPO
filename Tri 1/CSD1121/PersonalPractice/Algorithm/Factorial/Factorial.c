#include <stdio.h>

int main(void)
{
    int F;
    scanf("%d",&F);
    int value_Total = F;

    for (int i = F;i > 1;--i)
    {
        value_Total *= i-1;
    }
    printf("Factorial of %d is %d\n",F,value_Total);

}