/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Assignment 6: Linear Algebra and Arrays
@date 17/10/22
@brief
1.Reversing the value in array
2.Addition of 2 array
3.Scalay multiplication
4.Find dot product of 2 vector(this case array)
5.Find cross product of 2 vector(this case array)
6.Find Length of 2 vector(this case array)
*/
#include <stdio.h>
#include <math.h>
#include "q.h"

void reverse_array(int a[], int size)
{
    int temp = 0;
    for (int i =0 ; i < size/2 ; i++)
    {
        temp =  a[size-i-1];//take current value of opposite facing array and place it in temp
        a[size-i-1] = a[i];//switch opposite array value with current array value
        a[i] = temp;//input temp value current array
    }
}
void add_arrays(int const a[], int const b[], int c[], int size)
{
    for (int i = 0; i < size ; i++)
    {
        c[i] = a[i]+b[i];//pretty self explanatory
    }
}
void scalar_multiply(int a[ ], int size, int scale_factor)
{
    for(int i = 0; i < size ; i++)
    {
        a[i] *= scale_factor;//scalar
    }
}
int dot_product(int const a[ ], int const b[ ], int size)
{
    int sum = 0;
    for (int i =0;i < size ;i++)
    {
        sum += a[i]*b[i];
    }
    return sum;


}
void cross_product(int const a[ ], int const b[ ], int c[ ])
{
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = -((a[0]*b[2])-(a[2]*b[0]));
    c[2] = a[0]*b[1] - a[1]*b[0];

}
double length(int const a[ ], int size)
{
    double sum=0.0;
    for (int i = 0 ;i < size ;i++)
    {
        sum += powl(a[i],2);//power the current array value by 2 and add it to sum 
    }
    return sqrtl(sum);
}