/*
* fib.h - header file that declares the necessary C standard library
* header files (none in this example) and function fibonacci.
* Clients are expected to include this header file as an interface
* to the implementation of function fibonacci.
* Notice that the function returns different error codes depending on
* how the input is malformed: it returns -1 if the passed array base
* address is 0 and -2 if array size is <= 0.
* Also notice that the function returns 0 for successful generation
* of Fibonacci sequence.
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
int fibonacci(unsigned int array[], int size);
