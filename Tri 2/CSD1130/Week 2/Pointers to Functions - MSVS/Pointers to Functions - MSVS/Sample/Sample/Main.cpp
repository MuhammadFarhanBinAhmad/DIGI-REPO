// ---------------------------------------------------------------------------
// Project Name		:	Sample
// File Name		:	Main.cpp
// Author			:	DigiPen - CSD1130
// Creation Date	:	19/01/2021
// Purpose			:	Examples on how to use function pointers
// History			:
// ---------------------------------------------------------------------------

#include <stdio.h>

//Test01: Testing - basic pointer to function
namespace Test01
{
	void	Foo(void)
	{
		printf("Foo\n");
	}

	float	Boo(float a, float b)
	{
		return a + b;
	}
		
	void Run()
	{
		//----------------------------------------
		//Declaring a function pointer to Foo()

		void(*pfFoo)(void) = nullptr;
		pfFoo = Foo;
		//pfFoo = &Foo; // Also applicable

		//----------------------------------------
		//Using the function pointer to call Foo()
		pfFoo();//this will call Foo()
		//(*pfFoo)(); // Also applicable


		//----------------------------------------
		//Declaring a function pointer to Boo()[]

		float(*pfBoo)(float, float) = nullptr;
		pfBoo = Boo;//give address of Boo
		//pfBoo = &Boo; // Also applicable

		//----------------------------------------
		//Using the function pointer to call Boo(3, 4)
		printf("Result: %f\n", pfBoo(3, 4));
		//printf("Result: %f\n", (*pfBoo)(3, 4)); // Also applicable
	}
}

//Test02: Testing - array of function pointers
namespace Test02
{
	void Foo1(void)
	{
		printf("Foo1\n");
	}

	void Foo2(void)
	{
		printf("Foo2\n");
	}

	void Foo3(void)
	{
		printf("Foo3\n");
	}

	void Foo4(void)
	{
		printf("Foo4\n");
	}

	void Foo5(void)
	{
		printf("Foo5\n");
	}

	void Run()
	{
		int i;

		//----------------------------------------
		// Creating an array of function pointers
		void(*arrayFP[])(void) = { Foo1, Foo2, Foo3, Foo4, Foo5 };

		//----------------------------------------
		// Calling all the 5 functions sequentially in a for loop
		for (i = 0; i < 5; ++i)
			arrayFP[i]();
	}
}

//Test03: Testing - typedef a function pointer
namespace Test03
{
	typedef void(*FP)(int);

	void Foo1(int a)
	{
		printf("Foo1: %i\n", a * 10);
	}

	void Foo2(int a)
	{
		printf("Foo2: %i\n", a * 20);
	}

	void Foo3(int a)
	{
		printf("Foo3: %i\n", a * 30);
	}

	void Foo4(int a)
	{
		printf("Foo4: %i\n", a * 40);
	}

	void Foo5(int a)
	{
		printf("Foo5: %i\n", a * 50);
	}

	void Run()
	{
		//----------------------------------------
		// Creating an array of function pointers
		//void (*arrayFP[])(int) = {Foo1, Foo2, Foo3, Foo4, Foo5};
		// or
		// using typedef
		FP	arrayFP[5] = { Foo1, Foo2, Foo3, Foo4, Foo5 };


		//----------------------------------------
		//Call the first 2 functions individually (with input = 1)
		arrayFP[0](1);
		(*arrayFP[1])(1);
	}
}

//Test04: Testing - passing a function pointer "pf" as a parameter to another function "Calculations"
namespace Test04
{
	float Calculations(float a, float b, float(*pf)(float, float))
	{
		float result = pf(a, b);
		return result;
	}

	//The following 4 functions "Plus", "Minus", Multiply", "Divide" have the same signature as the
	//function pointer "pf"
	inline float Plus(float a, float b)
	{
		return a + b;
	}

	inline float Minus(float a, float b)
	{
		return a - b;
	}

	inline float Multiply(float a, float b)
	{
		return a*b;
	}

	inline float Divide(float a, float b)
	{
		return a / b;
	}


	void Run()
	{
		//----------------------------------
		//Use the "Calculation" function to call one of the defined functions with
		//the following input: a = 3 and b = 5
		printf("Result: %f\n", Calculations(3, 5, Minus));
	}
}

//Test05: Testing - returning a function pointer "pf" from a function "GetSign"
namespace Test05
{
	typedef float(*PF)(float, float);

	float Calculations(float a, float b, PF pf)
	{
		float result = pf(a, b);
		return result;
	}


	inline float Plus(float a, float b)
	{
		return a + b;
	}

	inline float Minus(float a, float b)
	{
		return a - b;
	}

	inline float Multiply(float a, float b)
	{
		return a*b;
	}

	inline float Divide(float a, float b)
	{
		return a / b;
	}

	// ---------------------------------
	// The "GetSign" function (definition). returns one of the defined functions above.
	// returnedType GetSign(const char sign)
	PF GetSign(const char sign)
	{
		switch (sign)
		{
		case '+':
			return Plus;

		case '-':
			return Minus;

		case '*':
			return Multiply;

		case '/':
			return Divide;

		default:
			return 0;
		}
	}

	void Run()
	{
		// ---------------------------------
		// The "GetSign" function is used here as follow
		printf("Result: %f\n", Calculations(3, 5, GetSign('+')));
	}
}

int main()
{
	//Uncomment one line at a time, to run each unit-test separately

	//Test01::Run();
	Test02::Run();
	//Test03::Run();
	//Test04::Run();
	//Test05::Run();

	return 0;
}
