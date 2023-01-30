/*
* max.c - source file containing C code for illustrating idea of functions.
* The source file illustrates the implementation of max algorithm that 
* finds the larger of two integer values.
*
* Input (from standard input): two integer values
* Side effect of program: Write to standard output larger of two integer values
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror max.c -o max.out
*
* Run: ./max.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf
int max(int, int); // this is a prototype for function max

int main(void) {
  printf("Enter two integer values: ");
  int vone, vtwo;
  scanf("%d %d", &vone, &vtwo);
  int largest = max(vone, vtwo);
  printf("Larger of %d and %d is %d\n", vone, vtwo, largest);

  return 0;
}

int max(int x, int y) {
  int max_val;
  if (x > y) {
    max_val = x;
  } else {
    max_val = y;
  }
  return max_val;
}
