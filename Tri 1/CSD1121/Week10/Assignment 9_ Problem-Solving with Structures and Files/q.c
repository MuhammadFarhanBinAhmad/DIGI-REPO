/*
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Assignment 9: Problem-Solving with Structures and Files
@date 07/11/22
@brief The
program will print a report giving the maximum wave height for the tsunamis recorded in a data file. In addition to the maximum wave height, the report must include 
the average wave height and the location of all tsunamis with a wave height higher than the average height. All heights in the data file are measured in meters
*/
#include <stdio.h>
#include <string.h>
#include "q.h"

int read_data(char const *file_name, struct Tsunami *arr, int max_cnt)
{
    //Read file
    FILE *textfile = fopen(file_name,"r");
    int total = 0;

    char buffer[255];//set buffer for the char in txtx file

    //check if file exist and is open
    if (textfile == NULL)
    {
        return 0;
    }
    
     while(fgets(buffer,max_cnt,textfile) != NULL)
     {
        sscanf(buffer, "%d %d %d %d %lf %81[^\n]", &arr[total].month, &arr[total].day, &arr[total].year, &arr[total].fatalities, &arr[total].height, arr[total].location);
        total++;//count total tsunami
     }


    return total;

}
void print_info(struct Tsunami const *arr, int size, FILE *out_stm)
{

    for(int i = 0; i < size ; i++)
    {
        fprintf(out_stm,"%02d %02d %d %6d %5.2lf %s\n",arr[i].month,arr[i].day,arr[i].year,arr[i].fatalities,arr[i].height,arr[i].location);//print all the respective value for all the tsunami
    }
}
double get_max_height(struct Tsunami const *arr, int size)
{
    double maxheight =0;

    for (int i  =0; i < size; i++)
    {
        if (arr[i].height > maxheight)
        {
            maxheight = arr[i].height;//check which tsunami has the highest height
        }
    }
    return maxheight;
}
double get_average_height(struct Tsunami const *arr, int size)
{
    double totalheight = 0;

    for (int i =0 ; i < size; i++)
    {
        totalheight+= arr[i].height;
    }

    return totalheight/(double)size;
}
void print_height(struct Tsunami const *arr, int size, double height, FILE *out_stm)
{

    for (int i =0; i < size ; i++)
    {
        if (arr[i].height > height)
        {
            fprintf(out_stm,"%.2lf %s\n",arr[i].height,arr[i].location);//print all tsunami whose height is higher than the average value
        }
    }
}
