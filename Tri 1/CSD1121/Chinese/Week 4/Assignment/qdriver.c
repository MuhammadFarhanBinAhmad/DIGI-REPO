/*!
@file qdriver.c
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

int main(void)
{
	int value;
	while (1 == scanf("%d", &value)) {
		if (value <= 0 || value >= 4000) {
			continue;
		}
		decimal_to_roman(value);
	}
	return 0;
}