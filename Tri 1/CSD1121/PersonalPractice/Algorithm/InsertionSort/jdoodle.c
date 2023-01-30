
//Insertion sort
#include<stdio.h>

int value[] = {3,1,5,2,4,6,9,8,10,123,341,12,345,99,100,0,456};
int current_index=0;

void CheckBackValue();
void CheckFrontValue();
void SortValue();

void CheckBackValue()
{
    int a =value[current_index];
    int b =value[current_index-1]; 
        //didnt know can do use operator like this
        a<b?
        value[current_index] = b,
        value[current_index-1] = a,
        current_index--,//use to check previous element if 
        CheckBackValue():
        CheckFrontValue();

}
void CheckFrontValue()
{
    if (current_index+1 < sizeof(value)/sizeof(value[0]))
    {
        int a =value[current_index];
        int b =value[current_index+1];
        
        a>b?
        value[current_index+1] = a,
        value[current_index] = b,
        CheckBackValue():
        SortValue();
    }
}

void SortValue()
{
    if (current_index+1 < sizeof(value)/sizeof(value[0]))
    {
        current_index++;
        CheckBackValue();
    }
}

int main() 
{
    SortValue();
    for(int i =0 ; i < sizeof(value)/sizeof(value[0]) ; i++)
    {
        printf("%d\n",value[i]);
    }
}