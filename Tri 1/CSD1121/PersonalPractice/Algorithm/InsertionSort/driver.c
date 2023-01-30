#include <stdio.h>
#include "Insertion.h"

#define SIZE 100

int arraysize[SIZE];

int main() 
{
    int v=0;
    printf("%d\n",v);
    int total_Number = read_data(arraysize,SIZE);//check total element filled in array
    SortValue(arraysize,total_Number);
    for(int i =0 ; i < total_Number ; i++)
    {
        printf("%d\n",arraysize[i]);
    }
    printf("int value index to find:");
    //scanf("%d",&value_TOFIND)?printf("%d",FindValue(arraysize,total_Number,value_TOFIND)):printf("Incorrect input");


}