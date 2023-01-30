/*!
@file q.c
@author MuhammadFarhanBinAhmad(b.muhammadfarhan)
@course IMGD
@section csd1121
@Assignment 5: Practicing Iteration by Computing Pi
@date 27/09/22
@brief
Calculating the approximention value of pi using 3 different formula: Trapezoid method,
The monte carlo(gambling no halal), and the leibniz method
*//*______________________________________________________________________*/
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//return an odd number value to be use in the trapezoid method
double GetOddNumber(int i)
{
	return 2.0 * i + 1;
}
double trapezoid_pi(int num_of_rects)
{
	double pi = 0.0;
	double value_Height =0.0;
	double value_Width = 2.0 / (double)num_of_rects;
	for (int i = 0; i < num_of_rects; ++i)
	{
		value_Height = sqrt(pow(2.0, 2) - pow((GetOddNumber(i) / 2.0) * value_Width, 2));
		pi += value_Height;
	}
	return pi * value_Width;
}
double montecarlo_pi(unsigned int seed, int num_of_trails)
{
	double value_Rand1, value_Rand2, value_Total, pi;
	double total_sum;
	srand(seed);

	for (int i = 0; i < num_of_trails; ++i)
	{

		value_Rand1 = (double)rand() / RAND_MAX;
		value_Rand2 = (double)rand() / RAND_MAX;
		value_Total = (value_Rand1 * value_Rand1) + (value_Rand2 * value_Rand2);

		if (value_Total <= 1)
		{
			total_sum++;
		}
	}

	pi = ((double)total_sum / num_of_trails) * 4;
	return pi;

}
double leibniz_pi(int num_elements)
{
	double sum = 0.f, denominator, pi;

	for (int i = 0; i < num_elements; i++)
	{
		denominator = pow(-1, i) / (2 * i + 1);
		sum += denominator;
	}
	pi = 4 * sum;
	return pi;
}
