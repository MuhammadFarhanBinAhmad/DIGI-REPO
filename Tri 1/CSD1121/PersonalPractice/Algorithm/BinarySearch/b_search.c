//Insertion sort
#include<stdio.h>

int value[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

void FindValue(int value_ToFind,int centerindex)
{
    int mid;
    int top,bottom;
    //Searches value by "cutting" array in half
    if (value[centerindex] != value_ToFind)
    {
        //if current array pointed is lower,all value below than the current array is discarded 
        if (value_ToFind > value[centerindex])
        {
            bottom = centerindex;
            top = sizeof(value)/sizeof(value[0]) - 1;
            mid = bottom + (top/bottom);
            FindValue(value_ToFind,mid);
        }
        //if current array pointed is higher,all value higher than the current array is discarded 
        if (value_ToFind < value[centerindex])
        {
            top = centerindex;
            mid = top/2;
            FindValue(value_ToFind,mid);
        }
    }
    else
    {
        printf("values index = %d",centerindex);
    }
}

int main() 
{
    int value_ToFind;
    int centerindex = ((sizeof(value)/sizeof(value[0]))/2)-1;
    scanf("%d",&value_ToFind);
    FindValue(value_ToFind,centerindex);
}