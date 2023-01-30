// TODO1: add file header documentation!!!

/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@ Assignment 7: Encryption/Decryption with Pointers
@date 22/10/22
@brief 1. Encrypts a plain text input file by writing the encrypted text into a ciphered text output file.
2. Decrypts a ciphered text input file into a deciphered text output file.
3. Counts the number of words in the deciphered text file
*/

#include "q.h" // included because q.c requires access to ASCII_COUNT
#include <stdio.h>
// TODO2: include other C standard library headers. for reasons 
// explained in previous assignments/labs, think carefully about 
// the need to add an include file before you do so ...

// TODO3: define functions encrypt and decrpyt ...
int encrypt(int* letter,char keytext)
{
    int temp =0;
    temp = *letter + (int)keytext;
    return temp > 127? temp - 127 -1:temp;//if value go over ascii value, will reset value
}
int decrypt(int* letter,char keytext)
{
    int temp = 0;
    temp = *letter - (int)keytext;
    return temp < 0? temp +128:temp;//if value go below 0 value, will reset value
}
