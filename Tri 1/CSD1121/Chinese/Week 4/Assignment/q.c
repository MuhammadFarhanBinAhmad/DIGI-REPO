/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Assignment 4: Converting to Roman NumbersVirtual programming lab
@date 21/09/22
@brief
The algorithm belows takes in an int value thats which is being taken from txt file qinput.txt and convert of
them into roman numeral
*//*______________________________________________________________________*/
#include <stdio.h>
#include "q.h"

//Setting all neseccary data
int character_Value[18] = { 1000,900,500,400,100,90,50,40,10,9,8,7,6,5,4,3,2,1 };
char* character_Char[18] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX","VIII","VII","VI","V","IV","III", "II", "I" };
int character_Total[18];

void decimal_to_roman(int decimal_value)
{
	int l = 0;

	while (decimal_value >= 1)
	{
		//Check value. If value if big enough, it will minus out biggest value that current numeral could
		//Check value and see how many time it can be divided with the current numeral value.
		decimal_value >= character_Value[l] ? decimal_value -= ((character_Total[l] = (decimal_value / character_Value[l])) * character_Value[l]) : decimal_value;
		for (int i = 0; i < character_Total[l]; i++)
		{
			printf("%s", character_Char[l]);
		}
		l++;
	}
	printf("\n");
	//Erase value from current call to ensure a empty array for the next value
	for (int i = 0; i < 18; i++)
	{
		character_Total[i] = 0;
	}
}