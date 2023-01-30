/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Lab 4: Formatted Console I/O
@date 23/09/22
@brief
The user will input in a certain value of money and the system will convert them to its money
type(1000,100,50 etc.) and will out the result
*//*______________________________________________________________________*/
#include <stdio.h>

int money_Value[11] = { 10000,5000,1000,500,200,100,50,20,10,5,1 };//all in cents
int total_Type[11];
void go(void)
{
	while (1)
	{
		int dollar, cents;
		int input = scanf("%d.%d", &dollar, &cents);
		if (input < 2)
		{
			printf("Please enter total value: Program ended\n");
			return;
		}
		if (dollar < 0)
		{
			printf("Please enter total value: Program ended\n");
			return;
		}
		if (cents < 0 || cents > 99)
		{
			printf("Please enter total value: Program ended\n");
			return;
		}
		int total_money = ((dollar * 100) + cents);//in cents
		printf("Please enter total value: \n");
		printf("+----+--------------+-------+\n");
		printf("| #  | Denomination | Count |\n");
		printf("+----+--------------+-------+\n");
		int t = 0;
		while (t <= 10)
		{
			total_money >= 1 ? total_money -= ((total_Type[t] = total_money / money_Value[t]) * money_Value[t]) : total_money;
			if (money_Value[t] >= 100)
			{
				int td = money_Value[t] / 100;
				printf("| %-2.d | %9.d.00 | %5d |\n", t + 1, td, total_Type[t]);
			}
			else
			{
				int z = 0;
				printf("| %-2.d | %9d.%.2d | %5d |\n", t + 1, z, money_Value[t], total_Type[t]);
			}
			t++;
		}
		printf("+----+--------------+-------+\n");
	}
}