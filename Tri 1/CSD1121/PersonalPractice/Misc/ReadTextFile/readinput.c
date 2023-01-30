#include <stdio.h>

#define SIZE 100

int input[SIZE];

void ReadData(int array[],int max_Size)
{
    int index=0;
    int val = 0;
    //while((scanf("%d%*d",&val) != EOF)&& index < max_Size)//Always skip the 2nd value regardless of space in between
    //EOF - Read till the last readable text
    //Will read till EOF and that the array size is big enough to fit all the value in the text
    while((scanf("%d",&val) != EOF)&& index < max_Size)
    {
        array[index++] = val;
    }
    for(int i =0 ; i < index;i++)
    {
        printf("%d\n",input[i]);
    }
}

int main()
{
    ReadData(input,SIZE);
}