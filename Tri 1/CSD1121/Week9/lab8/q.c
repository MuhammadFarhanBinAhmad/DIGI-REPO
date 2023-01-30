/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 8: Character Counter
@date 28/10/22
@brief 1. Check the character in the file to see if its Latin character,non latin character or a control char
*/
#include <stdio.h>   // do not remove

void initialize(int latin_freq[], int size, int *ctrl_cnt,int *non_latin_cnt)
{
    for (int i = 0 ; i < size;++i)
    {
        latin_freq[i] = 0;//clear out freq array 
    }
    *ctrl_cnt = *non_latin_cnt =0;//clear out variables
}
int CheckLatin(int input)
{
    int index = -1;
    //Check char to see if its a latin char
    if (('a' <= input && input <= 'z'))//check if its lowercase
    {
        index = input - 'a';
    }
    else if (('A' <= input && input <= 'Z'))//check if its uppercase
    {
        index = input - 'A';
    }
    return index;
}

//Check its a control chaar
int CheckNonLatin(int input)
{
    if (input == '\a'||input == '\b'||input == '\f'|| input == '\n'||input == '\r'||input == '\t'||input == '\v')
    {
        return 1;
    }
    return 0;
}
void wc(FILE *ifs, int latin_freq[], int *ctrl_cnt, int *non_latin_cnt)
{
    char current;
    int index;

    while ((current = (char)fgetc(ifs)) !=EOF)
    {
        if((index = CheckLatin(current)) >= 0)
        {
            ++latin_freq[index];
        }
        else if(CheckNonLatin(current))
        {
            ++*ctrl_cnt;
        }
        else{
            ++*non_latin_cnt;//ones thats not a control or latin
        }
    }

}
void print_freqs(int const latin_freq[], int size, int const *ctrl_cnt,int const *non_latin_cnt)
{
    for (int i = 0 ; i < size; ++i )
    {
        printf("%-10c",'a' + i);
    }
    printf("\n");

    int latin_Count = 0;
    for (int i =0 ;i < size ;++i)
    {
        printf("%-10d",latin_freq[i]);
        latin_Count += latin_freq[i];//count total latin char
    }
    printf("\n\n");

    printf("%-18s:%8d\n","Latin Letters",latin_Count);
    printf("%-18s:%8d\n","Non-Latin Letters",*non_latin_cnt);
    printf("%-18s:%8d\n","Control Letters",*ctrl_cnt);

    //I dont like formatting
}