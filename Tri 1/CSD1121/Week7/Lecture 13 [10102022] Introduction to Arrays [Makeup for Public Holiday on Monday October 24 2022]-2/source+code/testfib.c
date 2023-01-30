/*
* testfib.c - source file illustrating a main function to test
* function fibonacci declared in fib.h.
* After generating the Fibonacci sequence, function main prints a
* pretty table consisting of 5 columns.
*
* Always compile (only) with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror 
*            -c testfib.c -o testfib.o
* Link C standard library functions and fib.o and testfib.o 
* to create executable: gcc fib.o testfib.o -o testfib.out
*
* Run: ./testfib.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include "fib.h"
#include <stdio.h>

/*
#define SIZE 40 defines SIZE to be a synonym for 40.
The use of #define allows us to write code that is parameterized by a small
set of constants. If we ever want to change a parameter, we need only
change its definition. In this case, changing #define SIZE 40 to
#define SIZE 200 is simpler than changing every occurrence of 40 throughout
the code. More importantly, changing one line of code is less likely to
introduce bugs than changing many lines of code.
*/
#define SIZE 40

int main(void) {
  // define an array of SIZE integers and initialize the first two
  // elements to 1 and 1 and the remaining elements to 0
  unsigned int fib[SIZE];

  // generate Fibonacci sequence ...
  if (fibonacci(fib, SIZE) < 0) {
    printf("Unable to generate Fibonacci sequence!!!\n");
    return 0;
  }
  // otherwise, print a pretty table of Fibonacci sequence with 5 columns ...
  printf("First %d elements of Fibonacci sequence:\n", SIZE);
  for (int i = 0; i < SIZE; ++i) {
    printf("%-10u", fib[i]);
    if (i && ((i+1)%5 == 0)) printf("\n");
  }
  return 0;
}
