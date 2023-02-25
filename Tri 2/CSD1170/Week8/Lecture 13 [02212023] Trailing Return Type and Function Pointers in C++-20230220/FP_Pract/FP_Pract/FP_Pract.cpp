// FP_Pract.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int add(int a, int b){return a + b;}
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

enum class Op : int { ADD, SUB, MUL, DIV };

int (*Select(char opcode))(int, int)
{
	switch (opcode)
	{
	case '+': return add;
	case '-': return subtract;
	case '*': return multiply;
	case '/': return divide;
	}
	return nullptr;
}

int compute(int (*callback)(int, int), int x, int y)
{
	return callback(x, y);
}

void print(int (*callback)(int, int), int x, int y)
{
	std::cout << callback(x, y) << std::endl;
}
void printname()
{
	std::cout << "cat" << '\n';
}
void printage()
{
	std::cout << "12" << '\n';
}
void printcompany()
{
	std::cout << "pussy" << '\n';
}

int main()
{
	char opcode;
	void(*pf)(void);//declare void pointer function

	//Constantly changing function the pointer function is pointing
	pf = printname;
	pf();
	pf = printage;
	pf();
	pf = printcompany;
	pf();

	std::cin >> opcode;
	print(Select(opcode), 5, 5);//call print function that takes in a function pointer thats takes in a char and 2 int value



	// Array of function pointers offers the possibility of selecting
	// a function using an index ...
	// An array of function pointers is known as a jump table [among many other names] ...
	int (*math_func[]) (int, int) { add, subtract, multiply, divide};

	// evaluate multiplication expression ...
	std::cout << "2 * 3 = " << math_func[static_cast<int>(Op::MUL)](2, 3) << '\n';
	// evaluate more complex expression ...
	std::cout << "3.0 * (4.0 + 5.0) + 6.0 = "
		<< math_func[static_cast<int>(Op::ADD)](
			math_func[static_cast<int>(Op::MUL)](3, math_func[static_cast<int>(Op::ADD)](4, 5)), 6)
		<< '\n';

}
