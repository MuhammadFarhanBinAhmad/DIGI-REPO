/*
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 11 - Struct Arrays
@date 18/11/22
@brief 
implement a generic function print_data that takes in the address of an object of
any type, its size, with the number of hexadecimal digits per line of output, and prints out to the
console a layout similar to a hex editor interface.
*/

#include "q.h"

void print_data(const void* ptr, size_t size,size_t span)
{

    char *current = (char*)ptr;
    char* current_Hex = current;
    int current_pos = 0;
    int max = (int)span/4;

    while(current -(char*)ptr < (int)size)
    {
        printf("%x %x %x %x",current[0],current[1],current[2],current[3]);//print all hex value in current line of array
        current += 4;//move to next line of array

        current_pos++;//for formatting sake.sigh
        if (current_pos < max)
        {
        printf("   ");
        }
        else
        {
        //Make new line
        current_pos = 0;
        printf("   |");
        //write character
        while(current_Hex < current)
        {
            printf("   %c %c %c %c",current_Hex[0],current_Hex[1],current_Hex[2],current_Hex[3]);
            current_Hex += 4;//go next array
        }
        printf("\n");
        }
    }

}
