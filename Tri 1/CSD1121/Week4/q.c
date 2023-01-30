/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@tutorial Assignment 4 :Converting Decimal System to Roman Numeral System
@date 20/09/22
@brief
Task 1: Create a system in which it translate incoming decimal(int) value into roman numeral and print it on a text file
*//*______________________________________________________________________*/
#include <stdio.h>
#include "q.h"
void decimal_to_roman(int value)
{
	int M = 1000;
	int CM = 900;
	int D = 500;
	int CD = 400;
	int C = 100;
	int XC = 90;
	int L = 50;
	int XL = 40;
	int X = 10;
	int IX = 9;
	int VIII = 8;
	int VII = 7;
	int VI = 6;
	int V = 5;
	int IV = 4;
	int III = 3;
	int II = 2;
	int I = 1;

	int total_M ;
	int total_CM;
	int total_D;
	int total_CD;
	int total_C;
	int total_XC;
	int total_L;
	int total_XL;
	int total_X;
	int total_IX;
	int total_VIII;
	int total_VII;
	int total_VI;
	int total_V;
	int total_IV;
	int total_III;
	int total_II;
	int total_I;
	
	int value_Decimal = value;
	printf("%d: ",value_Decimal);
	//M
	if (value_Decimal >= M)
	{
		total_M = (value_Decimal / M);
		for (int i = 0; i < total_M; i++)
		{
			printf("M");
		}
		value_Decimal -= (total_M * M);
	}
	//printf("value left: %d", value_Decimal);
	//CM
	if (value_Decimal >= CM)
	{
		total_CM = (value_Decimal / CM);
		for (int i = 0; i < total_CM; i++)
		{
			printf("CM");
		}
		value_Decimal -= (total_CM * CM);
	}
	//D
	if (value_Decimal >= D)
	{
		total_D = (value_Decimal / D);
		for (int i = 0; i < total_D; i++)
		{
			printf("D");
		}
		value_Decimal -= (total_D * D);
	}
	//CD
	if (value_Decimal >= CD)
	{
		total_CD = (value_Decimal / CD);
		for (int i = 0; i < total_CD; i++)
		{
			printf("CD");
		}
		value_Decimal -= (total_CD * CD);
	}
	//C
	if (value_Decimal >= C)
	{
		total_C = (value_Decimal / C);
		for (int i = 0; i < total_C; i++)
		{
			printf("C");
		}
		value_Decimal -= (total_C * C);
	}
	//XC
	if (value_Decimal >= XC)
	{
		 total_XC = (value_Decimal / XC);
		for (int i = 0; i < total_XC; i++)
		{
			printf("XC");
			//printf("%d\n", total_XC);
		}
		value_Decimal -= (total_XC * XC);
	}
	if (value_Decimal >= L)
	{
		total_L = (value_Decimal / L);
		for (int i = 0; i < total_L; i++)
		{
			printf("L");
		}
		value_Decimal -= (total_L * L);
	}
	if (value_Decimal >= XL)
	{
		total_XL = (value_Decimal / XL);
		for (int i = 0; i < total_XL; i++)
		{
			printf("XL");
		}
		value_Decimal -= (total_XL * XL);
	}
	if (value_Decimal >= X)
	{
		total_X = (value_Decimal / X);
		for (int i = 0; i < total_X; i++)
		{
			printf("X");
		}
		value_Decimal -= (total_X * X);
	}
	if (value_Decimal >= IX)
	{
		total_IX = (value_Decimal / IX);
		for (int i = 0; i < total_IX; i++)
		{
			printf("IX");
		}
		value_Decimal -= (total_IX * IX);
	}
	if (value_Decimal >= VIII)
	{
		 total_VIII = (value_Decimal / VIII);
		for (int i = 0; i < total_VIII; i++)
		{
			printf("VIII");
		}
		value_Decimal -= (total_VIII * VIII);
	}
	if (value_Decimal >= VII)
	{
		 total_VII = (value_Decimal / VII);
		for (int i = 0; i < total_VII; i++)
		{
			printf("VII");
		}
		value_Decimal -= (total_VII * VII);
	}
	if (value_Decimal >= VI)
	{
		 total_VI = (value_Decimal / VI);
		for (int i = 0; i < total_VI; i++)
		{
			printf("VI");
		}
		value_Decimal -= (total_VI * VI);
	}
	if (value_Decimal >= V)
	{
		 total_V = (value_Decimal / V);
		for (int i = 0; i < total_V; i++)
		{
			printf("V");
		}
		value_Decimal -= (total_V * V);
	}
	if (value_Decimal >= IV)
	{
		 total_IV = (value_Decimal / IV);
		for (int i = 0; i < total_IV; i++)
		{
			printf("IV");
		}
		value_Decimal -= (total_IV * IV);
	}
	if (value_Decimal >= III)
	{
		 total_III = (value_Decimal / III);
		for (int i = 0; i < total_III; i++)
		{
			printf("III");
		}
		value_Decimal -= (total_III * III);
	}
	if (value_Decimal >= II)
	{
		 total_II = (value_Decimal / II);
		for (int i = 0; i < total_II; i++)
		{
			printf("II");
		}
		value_Decimal -= (total_II * II);
	}
	if (value_Decimal >= I)
	{
		 total_I = I;
		printf("I");
		value_Decimal -= (total_I * I);
	}
	printf("\n");
}