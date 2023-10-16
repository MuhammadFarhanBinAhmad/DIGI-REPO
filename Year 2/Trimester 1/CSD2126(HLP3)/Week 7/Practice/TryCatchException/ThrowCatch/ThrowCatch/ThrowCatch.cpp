// ThrowCatch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>

double division(float a, float b)
{
	if (b == 0)
	{
		throw "Division by zero";
	}
	return (a / b);
}
struct MyException : public std::exception 
{
	const char* what() const throw () 
	{
		return "C++ Exception";
	}
};
int main()
{
	//BASIC TRY THROW CATCH 
	float x = 10;
	float y = 10;
	float z = 0;
	
	try
	{
		z = division(x, y);
		std::cout << z;
	}
	catch(const char* msg)
	{
		std::cout << msg << '\n';
	}
	//Standard Exception
	try
	{
		throw MyException();
	}
	catch (MyException& e)
	{
		std::cout << "MyException caught\n";
		std::cout << e.what() << std::endl;
	}

	return 0;

}

