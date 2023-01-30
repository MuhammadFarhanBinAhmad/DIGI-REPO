/*
* sizes.c - source file containing C code for illustrating
* the sizeof operator on fundamental types.
*
* Input from standard input: None
* Side effect: Print values returned by sizeof operator on C fundamental
* data types.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror sizes.c -o sizes.out
*
* Run: ./sizes.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

int main(void) {
  printf("sizeof(char):        %lu\n", sizeof(char));
  printf("sizeof(short):       %lu\n", sizeof(short));
  printf("sizeof(int):         %lu\n", sizeof(int));
  printf("sizeof(long):        %lu\n", sizeof(long));
  printf("sizeof(long long):   %lu\n", sizeof(long long));
  printf("sizeof(float):       %lu\n", sizeof(float));
  printf("sizeof(double):      %lu\n", sizeof(double));
  printf("sizeof(long double): %lu\n", sizeof(long double));
  
  return 0;
}
