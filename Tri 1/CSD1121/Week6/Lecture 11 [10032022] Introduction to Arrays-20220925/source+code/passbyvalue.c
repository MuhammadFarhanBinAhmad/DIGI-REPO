/*
* passbyvalue.c - source file illustrating pass-by-value convention
* for scalar values that are plain data types and also array elements.
*
* Input from standard input: None
* Side effect of program: Print absolute values for several integer arguments.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra  
*                                   -Werror passbyvalue.c -o passbyvalue.out
*
* Run: ./passbyvalue.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

// function to compute and return absolute value of integer parameter ...
int myabs(int x);

int main(void) {
  // pass-by-value convention with scalar values
  int some_val = 5;
  int mod_val;
  mod_val = myabs(-some_val);
  printf("myabs(%d): %d\n", -some_val, mod_val);
  mod_val = myabs(some_val-12);
  printf("myabs(%d): %d\n", some_val-12, mod_val);
  mod_val = myabs(-2*some_val);
  printf("myabs(%d): %d\n", -2*some_val, mod_val);

#define SIZE (5)
  int scores[SIZE] = {-1, 1, -2, 2, -3};
  // pass each array element using pass-by-value convention
  for (int i = 0; i < SIZE; ++i) {
    printf("myabs(%d): %d\n", scores[i], myabs(scores[i]));
  }
  
  return 0;
}

// return absolute value of parameter x
int myabs(int x) {
  return x > 0 ? x : -x;
}
