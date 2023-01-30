/*
@file q.h
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
#include <stdio.h>
struct Datum
{
char upper;
char lower;
unsigned short int value;
};
typedef struct Datum DATUM;
typedef DATUM DATA[2];
void print_data(
const void* ptr, // Address of the first byte.
size_t size, // Total count of bytes.
size_t span // Count of bytes printed per line.
);