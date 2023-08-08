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
double trapezoid_pi(int num_of_rects);
double montecarlo_pi(unsigned int seed, int num_of_trails);
double leibniz_pi(int num_elements);
