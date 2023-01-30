#ifndef Q_H
#define Q_H

/*
@file q.h
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
typedef struct Tsunami
{
    int month,day,year,fatalities;
    double height;
    char location[81];
}Tsunami;

// TODO: Repeat function documentation block plus function declaration for remaining functions
int read_data(char const *file_name, struct Tsunami *arr, int max_cnt);
void print_info(struct Tsunami const *arr, int size, FILE *out_stm);
double get_max_height(struct Tsunami const *arr, int size);
double get_average_height(struct Tsunami const *arr, int size);
void print_height(struct Tsunami const *arr, int size,
double height, FILE *out_stm);

#endif
