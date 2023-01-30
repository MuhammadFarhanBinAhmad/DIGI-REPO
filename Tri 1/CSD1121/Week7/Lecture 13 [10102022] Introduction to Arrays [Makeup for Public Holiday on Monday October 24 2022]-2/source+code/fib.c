/*
* fib.c - source file illustrating a function to generate Fibonacci 
* numbers using a for statement.
* Doing too much in function main is bad practice. A program tends to
* grow over time as more is required of it, so it is best to factor
* code into manageable functions. This modularity pays dividends: it
* allows modular thinking, where one doesn't have to recall how exactly
* a certain function is implemented but only what it accomplishes; it
* facilitates code reuse, in which a function is called in multiple
* contexts; and it is easier to maintain.
* Notice that the function returns different error codes depending on
* how the input is malformed: it returns -1 if the passed array base
* address is 0 and -2 if array size is <= 0.
* Also notice that the function returns 0 for successful generation
* of Fibonacci sequence.
*
* Always compile (only) with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror 
*            -c fib.c -o fib.o
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include "fib.h"

/*
Given an array, fib, with length n, computes the first n elements
of the Fibonacci sequence. Returns 0 to indicate success and negative
values for bad input.
*/
int fibonacci(unsigned int fib[], int N) {
  // check for well-formed input
  if (fib == 0) {
    return -1;
  }
  if (N <= 0) {
    return -2;
  }

  fib[0] = 1;
  if (N >= 2) {
    fib[1] = 1;
  }
  for (int i = 2; i < N; ++i) {
    fib[i] = fib[i-2] + fib[i-1];
  }
  // indicate successful completion
  return 0;
}
