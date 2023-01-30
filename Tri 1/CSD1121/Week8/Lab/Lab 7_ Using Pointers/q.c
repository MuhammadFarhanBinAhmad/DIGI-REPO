/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 7: Working with Pointers
@date 21/10/22
@brief Take in value in a txt file and reorgnising the value from the highest to the lowest value.
In addition, it will read a new value and,depending if its value is higher then whats already place, it react accordingly
*/
#include <stdio.h>
#include "q.h"
#include <stdlib.h>
size_t read_total_count(void)
{
    size_t size = 0;
    printf("Please enter the number of integers: ");
    scanf("%zu",&size);
    //check how many int are there in the text file
    if(size < 3)
    {
        //if less than 3, the program will shut down
        printf("There is no third largest number.\n");
        exit(EXIT_FAILURE);
    }
    return size;
}
void read_3_numbers(int* first, int* second, int* third)
{
    //take in the 3 int value addresses
    scanf("%d%d%d",first,second,third);
}
void swap(int* lhs, int* rhs)
{
    //swap value. Bigger value on the right,smaller on the left
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}
void sort_3_numbers(int* first, int* second, int* third)
{
    //Swap the 3 values from highest to lowest
    for (int i = 0; i <3;i++)
    {
    if (*first < *second)
    {
        swap(first,second);
    }
    if (*second < *third)
    {
        swap(second,third);
    }
    }

}
void maintain_3_largest(int number, int* first, int* second, int* third)
{
    //take in the new value and check if its larger than any of the current value
    if (number > *first)
    {
        int temp1 = *first;
        int temp2 = *second;
        *first = number;
        *second = temp1;
        *third = temp2;
        return;
    }
    if (number > *second)
    {
        int temp = *second;
        *second = number;
        *third = temp;
        return;
    }
    if (number > *third)
    {
        *third = number;
        return;
    }
}