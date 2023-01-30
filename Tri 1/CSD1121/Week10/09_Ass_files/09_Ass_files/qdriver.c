/*!
@file       qdriver.c 
@author     Swavek Wlodkowski (swavek.wlodkowski)
@course     CSD1120F20
@section    AB
@assignment 7
@date       30/10/2020
@brief      This file contains the test driver code.
            Do not modify or submit this file.
*//*__________________________________________________________________________*/

#include <stdio.h>		// feof(), fgets()
#include <stdbool.h>	// bool

#include "gamelib.h"

bool get_line(char text[])
{
	return (
		// File cursor has not reached the end of file...
		(!feof(stdin)) &&
		// ...and a line was fetched successfully.
		(fgets(text, LEN, stdin) != NULL)
	);
}

int main(void)
{
	Card accordion[N];
	char text[LEN];

	while (get_line(text))
	{
		load_game(text, accordion);
		play_game(accordion);
		display_game(accordion);
	}  
	
	return 0;
}
