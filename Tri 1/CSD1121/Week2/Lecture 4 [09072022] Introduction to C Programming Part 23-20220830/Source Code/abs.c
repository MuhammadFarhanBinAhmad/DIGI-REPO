/*
* abs.c - source file containing C code for illustrating idea of functions.
* The source file illustrates the implementation of modulus algorithm in a 
* function called abs
*
* Input from standard input: none
* Side effect of program: Write absolute of -10 to standard output
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror abs.c -o abs.out
*
* Run: ./abs.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf
int abs(int); // this is a prototype for function abs

int main(void) {
  int val = -10;
  printf("Absolute value of %d is %d\n", val, abs(val));

  return 0;
}

int abs(int x) {
  if (x < 0) {
    x = -x;
  }
  return x;
}
