/*
* abs-input.c - source file containing C code for illustrating idea of functions.
* The source file illustrates the implementation of modulus algorithm in a 
* function called abs
*
* Input from standard input: integer value
* Side effect of program: Write absolute of input value to standard output
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror abs-input.c -o abs-input.out
*
* Run: ./abs-input.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf
int abs(int); // this is a prototype for function abs

int main(void) {
  printf("Enter an integer value: ");
  int val;
  scanf("%d", &val);
  int aval = abs(val);
  printf("Absolute value of %d is %d\n", val, aval);

  return 0;
}

int abs(int x) {
  if (x < 0) {
    x = -x;
  }
  return x;
}
