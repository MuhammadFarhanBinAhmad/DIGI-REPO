#include <stdio.h>

#define SIZE 25

void min_max(int const arr[],int size,int *min,int *max)
{
    //int const arr[] is now only a read only array
    *min = *max = arr[0];
    printf("val_min address:%d\n",min);
    printf("val_max address:%d\n",max);
    // no need to make another variable to compare. We are just reading them
    for(int i = 0;i < size;i++)
    {
        *min = *min < arr[i]? arr[i]: *min; 
        *max = *max > arr[i]? arr[i]: *max; 
    }
}

int main()
{
    int array[SIZE];
    int val;
    int index;
    //read from text
    while((scanf("%d",&val)!=EOF) && index < SIZE)
    {
        array[index++] = val;
    }

    int val_Min,val_Max;
    min_max(array,index,&val_Min,&val_Max);//Send addresses if val_min and val_max
    printf("min value:%d\n",val_Min);
    printf("max value:%d\n",val_Max);

}