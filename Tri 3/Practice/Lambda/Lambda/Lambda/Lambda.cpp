// Lambda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

int main()
{
	//[] - capture caluse
	//() - pass parameters
	//{} - function definition
	//[cc](p) {fd};
	

	//Local Function use to print vector
	//The issue that its overkill
	//struct
	//{
	//	void operator()(int x)
	//	{
	//		std::cout << x << "\n";
	//	}
	//}something;

	//Lamda Example
	//[](int x) {std::cout << x << '\n'; }// Lamba use for trivial/small things. For this example, it's use to print out value

	//Lamda Example
	//[](int x) 
	//{ 
	//	if (x % 2 == 0)
	//	{
	//		std::cout << x << "is a even number\n";
	//	}
	//}


	//Lambda is more powerful than a normal function due to it having access to local variable of its enclose function
	int a = 3;
	int *d = &a;
	int f = 5;

	std::vector <int> v{ 2,3,7,14,23 };
	std::for_each(v.begin(), v.end(), 
		[d,&f](int x)
		{
			//is x divisible of d
			if (x % *d == 0)
			{
				std::cout << x << " is divisible by " << *d << '\n';
			}
			else
			{
				std::cout << x << " is not divisible by " << *d << '\n';
			}

			*d = 10;//value of variable cant be change unless its pass by ref/pointer
			f = 20;
		});

	//The capture clause can contain a operator to set what lambda value is pass by(eg.[=],[&])
	//[=] (int x) - Pass by copy
	//[&] (int x) - Pass by reference

	std::cout << "the value of d is " << *d << '\n';
	std::cout << "the value of f is " << f << '\n';
}
