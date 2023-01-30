#include <stdio.h>
//int a,b,c,d;
int x = 6;
int main(void)
{
    if (x>0)
    {
        switch(x)
        {
            case 1:
            x+=3;
            case 3:
            x+=1;
            break;
            case 6:
            x+=6;
            case 8:
            x*=8;
            break;
            default:
            x-=1;
        }
    }
    else x+=2;
        printf("%d",x);
}