//
/*
* Ass1:
* Intro to playing and making pointer
* Goal:
* Fimilarise yourself with the use of using pointers
* How to declare a function in the header file and define them in .cpp
* Some minor string manipulation
* How to print out test in console
*/
#include <iostream>
#include <vector>

#include "Pointer.h"

void test_01(My_Math* MM_01)
{
	MM_01->f_01 = 1.1f;
	MM_01->f_02 = 2.1f;
	MM_01->f_03 = 3.1f;
	MM_01->f_04 = 4.1f;

	MM_01->str_01 = "Roses are red. Violets are blue. I hate OS. And so will you";
	MM_01->str_02 = "IMGD,RTIS,uxgd,bfa";
	MM_01->str_03 = "LOLxd";
	MM_01->str_04 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "ADDITION TEST\n";
	std::cout << MM_01->Addition(&MM_01->f_01, &MM_01->f_02);
	std::cout << '\n';
	//Call the Addition function and print out the value of f_03 + f_04 here
	std::cout << "\n/-----------------------------------------------------------/\n";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "SUBTRACTION TEST\n";
	//Call the Subtraction function and print out the value of f_01 - f_02 here
	std::cout << '\n';
	//Call the Subtraction function and print out the value of f_01 - f_02 here
	std::cout << "\n/-----------------------------------------------------------/\n";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "DIVISION TEST\n";
	//Call the Division function and print out the value of f_01 / f_02 here
	std::cout << '\n';
	//Call the Division function and print out the value of f_03 / f_04 here
	std::cout << "\n/-----------------------------------------------------------/\n";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "MULTIPLICATION TEST\n";
	//Call the Multiplication function and print out the value of f_01 * f_02 here
	std::cout << '\n';
	//Call the Multiplication function and print out the value of f_01 * f_02 here
	std::cout << "\n/-----------------------------------------------------------/\n";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "SWAP VALUE\n";
	std::cout << "f_03 = " << MM_01->f_03 << " f_02 = " << MM_01->f_02 << std::endl;
	//Call function swap to swap the value fo f_03 and f_02
	std::cout << "f_03 = " << MM_01->f_03 << " f_02 = " << MM_01->f_02 << std::endl;
	std::cout << "\n/-----------------------------------------------------------/\n";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "SWAP VALUE\n";
	std::cout << "f_01 = " << MM_01->f_01 << " f_04 = " << MM_01->f_04 << std::endl;
	//Call function swap to swap the value fo f_01 and f_04
	std::cout << "f_01 = " << MM_01->f_01 << " f_04 = " << MM_01->f_04 << std::endl;
	std::cout << "\n/-----------------------------------------------------------/\n";

	std::cout << "/-----------------------------------------------------------/\n";
	std::cout << "ENCODE DECODE\n";
	std::cout << "Original text : " << MM_01->str_01 << '\n';
	//Encode the string str_01 with key number 3
	std::cout << "Encoded Text : " << MM_01->str_01 << '\n';	
	//Decode the string str_01 with key number 3
	std::cout << "Decoded Text : " << MM_01->str_01 << '\n';
	std::cout << "/-----------------------------------------------------------/\n";
}	


int main()
{
	My_Math MM_01;
	test_01(&MM_01);

}
