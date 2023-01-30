// TODO: File documentation block required
/*
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Assignment 10: Data Analysis Using the Heap
@date 07/11/22
@brief The program will open the data file, determine the count of grades in the file,
allocate appropriate memory in the heap as a container for the grades, store grades read from
the file in the previously allocated heap storage, and then analyze the data.
*/
#include "q.h" // we're including q.h here because we want to apply the DRY principle [see specs for additional info]
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int current_Index = 0;

double* read_data(char const *file_name, int *ptr_cnt)
{
    FILE *text_File = fopen(file_name,"r");

    double grade = 0;
    int count = 0;

    //Check if file exist and is successfully open
    if (text_File == NULL)
    {
        return 0;
    }

    //fscanf first so as to get total number in file
    while(fscanf(text_File,"%lf",&grade)!=EOF)
    {
        count++;
    }
    *ptr_cnt = count;

    //allocate space
    double *pg =  malloc(sizeof(double)*count);//reserve memory

    // check if malloc pass
    if (pg == NULL)
    {
        return 0;
    }

    //reset the file cursor to the start
    fseek(text_File,0,SEEK_SET);

    int index = 0;
    //reread the same file again. This time, to grab value and put them in array
    while(fscanf(text_File,"%lf",&grade)!=EOF)
    {
        pg[index] = grade;
        index++;
    }

    //rmb to always the door or ill rob your house and steal all your data
    fclose(text_File);

    return pg;

}
double max(double const *begin, double const *end)
{
    double highest_grade=0;//first val to compare

    //whilst begin is not the same address as end
    while(begin < end)
    {
        //Comparing
        if (*begin > highest_grade)
        {
            highest_grade = *begin;
        }
        //Next address
        begin++;
    }
    return highest_grade;
}
double min(double const *begin, double const *end)
{
    double lowest_grade=100;
    //whilst begin is not the same address as end
    while(begin < end)
    {
        //Comparing
        if (*begin < lowest_grade)
        {
            lowest_grade = *begin;
        }
        //Next address
        begin++;
    }
    return lowest_grade;
}
double average(double const *begin, double const *end)
{
    double total=0;
    int count = 0;
    //get total value
    while(begin < end)
    {
        total += *begin;
        begin++;
        count++;
    }
    //return avrg
    return total/(double)count;
}
double variance(double const *begin, double const *end)
{
    double mean_value = average(begin,end);
    double value = 0;
    int count = 0;
    while(begin < end)
    {
        count++;
        begin++;
    }
    
    begin -= count;//need reset to go back to original address to ensure proper value being use for the next calculation
    for (int i =0 ; i < count;++i)
    {
        value += pow((begin[i]- mean_value),2);
    }

    return value/(double)(count-1);
}
double std_dev(double const *begin, double const *end)
{
    return sqrt(variance(begin,end));
}
void SortingAlgo(double *base, int size)
{
    //The current element check with all the other elements in the array. If another array is smaller, both switch place.
    //At the end, the current element will the smallest compared to all the other in front of it
    for (int i =0;i < size;i++)
    {
        for (int j = 0;j<size;j++)
        {
            if (base[i] < base[j])
            {
                double temp;
                temp = base[i];
                base[i] = base[j];
                base[j] = temp;
            }
        }
    }
}
double median(double *base, int size)
{
    SortingAlgo(base, size);
    int middle = 0;
    double m = 0;
    //Check if its even number
    if (size%2 == 0)
    {
        middle = size/2;
        m = (base[middle]+base[middle-1])/(double)2;
        return m;
    }
    middle = size/2;
    return base[middle];
}

void ltr_grade_pctg(double const *begin, double const *end,double *ltr_grades)
{
    int count =0;
    while(begin < end)
    {
        count++;
        begin++;
    }
    begin -= count;//need reset to go back to original address to ensure proper value being use for the next calculation

    
    for (int i =0; i < count;i++)
    {
        if (begin[i]>= (double)90)
        {
            ltr_grades[0]++;
        }
        if (begin[i]>= (double)80 && begin[i]< (double)90)
        {
            ltr_grades[1]++;
        }
        if (begin[i]>= (double)70 && begin[i]< (double)80)
        {
            ltr_grades[2]++;
        }
        if (begin[i]>= (double)60 && begin[i]< (double)70)
        {
            ltr_grades[3]++;
        }
        if (begin[i] < (double)60)
        {
            ltr_grades[4]++;
        }
    }
    for (int i =0; i < TOT_GRADE;i++)
    {
        ltr_grades[i] = (ltr_grades[i]/count) * 100;
    }
}
// TODO: Include all necessary C standard library headers 

// TODO: Definitions of functions declared in q.h go here ...
