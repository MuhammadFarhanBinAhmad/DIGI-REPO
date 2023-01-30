/*!
@file q.h
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 6: Problem Solving with Arrays:Statistical Measurements
@date 11/10/22
@brief
Caculate the standard division from a list of grades(I remember doing this in secondary school)*/
int read_data(double array[], int max_count);
int max_index(double const arr[], int size);
int min_index(double const arr[], int size);
double mean(double const arr[], int n);
double variance(double const arr[], int size);
double std_dev(double const arr[], int size);

