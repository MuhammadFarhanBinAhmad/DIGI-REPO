#include<stdio.h>
#include<stdlib.h>
int main() 
{
    char *str = "5892582154789254";
    
    int count =0;
    
    while (*str)
    {
        count++;
        str++;
    }
    str -= count;
    
    int *num = malloc(sizeof(int) * count);
    
    while(*str)
    {
        *num = *str - 48;
        printf("%d ",*num);
        str++;
        num++;
    }
    printf("\n%d",sizeof(num[0]));
}