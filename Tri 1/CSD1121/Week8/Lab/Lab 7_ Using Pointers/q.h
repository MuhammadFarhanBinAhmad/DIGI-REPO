/*!
@file q.h
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 7: Working with Pointers
@date 21/10/22
@brief Take in value in a txt file and reorgnising the value from the highest to the lowest value.
In addition, it will read a new value and,depending if its value is higher then whats already place, it react accordingly
*/
#include <stdio.h>
#include <stdlib.h>
//size_t read_total_count(void) - check how many int value is in the txt file(Assuming all the value in the file is all number)
//void read_3_numbers(int* first, int* second, int* third)//Read the value in the txt file
//void swap(int* lhs, int* rhs)//Swap position of the value. Smaller on the right, largest on the left
//void sort_3_numbers(int* first, int* second, int* third)//sort value from highest(left side) to the lowest(right side)
//void maintain_3_largest(int number, int* first, int* second, int* third)//Insert new value and sort to the 3 largest(if needed to)
size_t read_total_count(void);
void read_3_numbers(int* first, int* second, int* third);
void swap(int* lhs, int* rhs);
void sort_3_numbers(int* first, int* second, int* third);
void maintain_3_largest(int number, int* first, int* second, int* third);
