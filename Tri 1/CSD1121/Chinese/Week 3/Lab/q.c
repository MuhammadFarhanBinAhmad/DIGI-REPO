/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@tutorial Lab 3: Problem Solving, I/O, and Expressions
@date 16/09/22
@brief 
Task 1:Devising an algorithm and creating a function that finds the
Wall length, Tile width,number of tiles and the gap at each end and outputting
the value.
Task 2:Devising an algorithm and creating a function that finds the
remaining money you have left in coin types(Loonies,half-loonies etc.)
and outputting the value.
*//*______________________________________________________________________*/
#include <stdio.h>

void tile(double WL, double TW)
{
	int pair = (int)((WL - TW) / (2 * TW));
	int tiles = 1 + (2 * pair);
	double gap = ((WL - (double)tiles * TW) / 2);

	printf("Wall length: %.2f | Tile width: %.2f\n", WL,TW);
	printf("Number of tiles: %d\n", tiles);
	printf("Gap at each end: %.2lf\n", gap);
}
void dispense_change(void)
{
	//Money values
	/*
	* Loonies - $1.00
	* Half-loonies - $0.50
	* Quater - $0.25
	* Dimes - $0.10
	* Nickel - $0.05
	* Penny - $0.01
	*/
	int price_Dollar;
	int price_Cent;
	int price_Total = 0;
	int total_Cash;//in cent
	scanf("%d.%d %d", &price_Dollar,&price_Cent,&total_Cash);

	//converting all in cent
	price_Dollar *= 100;
	total_Cash *=  100;
	price_Total = price_Dollar + price_Cent;

	//calculating total cash left(in cent)
	int remaining_Cash = total_Cash - price_Total;

	int value_Loonies = 100;
	int value_HalfLoonies = 50;
	int value_Quarter = 25;
	int value_Dimes = 10;
	int value_Nickles = 5;
	int value_Pennies = 1;

	int total_Loonies=0;
	int total_HalfLoonies=0;
	int total_Quarter=0;
	int total_Dimes=0;
	int total_Nickles=0;
	int total_Pennies=0;

	//Finding total coin needed for each coin type
	if (remaining_Cash > value_Loonies)
	{
		total_Loonies = remaining_Cash / value_Loonies;
		int i = total_Loonies * value_Loonies;
		remaining_Cash -= i;
	}
	if (remaining_Cash > value_HalfLoonies)
	{
		total_HalfLoonies = remaining_Cash / value_HalfLoonies;
		int i = total_HalfLoonies * value_HalfLoonies;
		remaining_Cash -= i;
	}
	if (remaining_Cash > value_Quarter)
	{
		total_Quarter = remaining_Cash / value_Quarter;
		int i = total_Quarter * value_Quarter;
		remaining_Cash -= i;
	}
	if (remaining_Cash > value_Dimes)
	{
		total_Dimes = remaining_Cash / value_Dimes;
		int i = total_Dimes * value_Dimes;
		remaining_Cash -= i;
	}
	if (remaining_Cash > value_Nickles)
	{
		total_Nickles = remaining_Cash / value_Nickles;
		int i = total_Nickles * value_Nickles;
		remaining_Cash -= i;
	}
	if (remaining_Cash >= value_Pennies)
	{
		total_Pennies = remaining_Cash;
	}
	printf("%d loonies + %d half-loonies + %d quarters + %d dimes + %d nickels + %d pennies\n", 
		total_Loonies,total_HalfLoonies, total_Quarter, total_Dimes, total_Nickles, total_Pennies);
}

