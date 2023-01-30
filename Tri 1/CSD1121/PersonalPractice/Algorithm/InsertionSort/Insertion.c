#include <stdio.h>
#include "insertion.h"
int current_index=0;

int read_data(int array[], int array_Size)
{
    int index = 0;
    int num = 0;
    //read values from selected text file and place it in array
    while ( (scanf("%d",&num)!=EOF) && index < array_Size ) 
    {
        array[index++] = num;
    }
    return index;
}
void CheckBackValue(int array[],int array_Size)
{
    int a =array[current_index];
    int b =array[current_index-1]; 
        //didnt know can do use operator like this
        a<b?
        array[current_index] = b,
        array[current_index-1] = a,
        current_index--,//use to check previous element if 
        CheckBackValue(array,array_Size):
        CheckFrontValue(array,array_Size);

}
void CheckFrontValue(int array[],int array_Size)
{
    if (current_index+1 < array_Size)
    {
        int a =array[current_index];
        int b =array[current_index+1];
        
        a>b?
        array[current_index+1] = a,
        array[current_index] = b,
        CheckBackValue(array,array_Size):
        SortValue(array,array_Size);
    }
}

void SortValue(int array[],int array_Size)
{
    if (current_index+1 < array_Size)
    {
        current_index++;
        CheckBackValue(array,array_Size);
    }
}
int FindValue(int array[],int array_Size,int value_TOFIND)
{
    return 0;
}