/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@tutorial Assignment 3:Formatted Console Output
@date 12/09/22
@brief This script will convert an inputted fahrenheit value into celsius and kelvin and will list it down in a list*/
//fahrenheit- 0
//celcius - -17.78
//Kelvin - 255.37
//temp is in fahrenheit
#include <stdio.h>  // declaration of printf
#include "q.h"
/*hold a int parameter which is the temperature value for fahrenheit in which it will converted to celcius and kelvin
and output all 3 value on a table
*/
void temp_converter(int temp)
{
	int temp_fahrenheit = temp;
	double temp_Celcius = ((double)temp - 32) * 5/9;
	double temp_Kelvin = ((double)temp - 32) *5/9 + 273.15;

	printf("Fahrenheit     Celsius        Kelvin         \n");
	printf("---------------------------------------------\n");
	printf("%-15d%-15.2lf%-15.2lf\n",temp_fahrenheit,temp_Celcius,temp_Kelvin);
}