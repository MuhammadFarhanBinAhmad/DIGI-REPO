/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 6: Problem Solving with Arrays:Statistical Measurements
@date 11/10/22
@brief
Caculate the standard division from a list of grades(I remember doing this in secondary school)*/
#include <stdio.h>
#include <math.h>
#include "q.h"

int read_data(double array[], int max_count)
{
    int i = 0;
    double num = 0;
    while ( (scanf("%lf", &num) != EOF) && i < max_count ) 
    {
        array[i++] = num;
    }
    return i;
}
//calculate highest grade value
int max_index(double const arr[], int size)
{
    double num = 0;
    double max = 0;
    int index = 0;
    for (int i = 0; i < size; ++i) 
    {
        num = arr[i];
        if (max < num)
        {
            max = num;
            index = i; 
        }
    }
    return index;
}
//calculate lowest grade value(gg my dude)
int min_index(double const arr[], int size)
{
    double num = 0;
    double min = arr[0];//starting compare value
    int index=0;
    for (int i = 0; i < size; i++) 
    {
        num = arr[i];
        if (min > num)
        {
            min = num;
            index = i; 
        }
    }
    return index;
}
//calculate average grade value 
double mean(double const arr[], int size) 
{
    double sum_Total = 0;
    for (int i = 0; i < size; i++)
    {
        sum_Total += arr[i];
    }
    return  sum_Total / (double)size;

}
double variance(double const arr[], int size)
{
    //check if size of array is more then 2(for auto grader compiler)
    if (size < 2)
    {
        return 0;
    }
    double mean_value = mean(arr,size);//call mean function to get average value
    double total_data_point=0;
    //calculate variant value
    for (int i = 0; i < size; ++i)
    {
        total_data_point += pow((arr[i] - mean_value),2);
    }
    return total_data_point/--size;
}
//calculate standard division value
double std_dev(double const arr[], int size)
{
    return sqrt(variance(arr,size));
}

