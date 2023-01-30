/*
* whileloop.c - source file illustrating while iteration statement that
* modifies arbitrarily large arrays.
*
* Input from standard input: None
* Side effect of program: Print pretty output of the first 40
* numbers in Fibonnaci sequence.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror 
            whileloop.c -o whileloop.out
*
* Run: ./whileloop.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

#define SIZE 40

int main(void) {
  // define an array of SIZE integers and initialize the first two
  // elements to 1 and 1 and the remaining elements to 0
  unsigned int fib[SIZE] = {1, 1};

  // the while loop form makes the Fibonacci computations more clearer:
  int i = 2;
  while (i < SIZE) {
    fib[i] = fib[i-2] + fib[i-1];
    ++i;
  }

  // print a pretty table of Fibonacci sequence with 5 columns ...
  printf("First %d elements of Fibonacci sequence:\n", SIZE);
  for (int i = 0; i < SIZE; ++i) {
    printf("%-10u", fib[i]);
    if (i && ((i+1)%5 == 0)) printf("\n");
  }
  
  return 0;
}
