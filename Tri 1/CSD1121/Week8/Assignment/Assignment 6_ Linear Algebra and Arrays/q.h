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
void reverse_array(int a[], int size);
void add_arrays(int const a[], int const b[], int c[], int size);
void scalar_multiply(int a[ ], int size, int scale_factor);
int dot_product(int const a[ ], int const b[ ], int size);
void cross_product(int const a[ ], int const b[ ], int c[ ]);
double length(int const a[ ], int size);
