/*
* classify.c - source file illustrating the use of both the
* for statement and switch statement.
*
* Input from standard input: Read integer values and specify how many of 
* these values are even, odd, zero, and unknown valued.
* Side effect of program: Print count of even, odd, zero, and unknown 
* valued values.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror classify.c -o classify.out
*
* Run: ./classify.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

int main(void) {
  printf("Enter count of numbers to read: ");
  int N;
  scanf("%d", &N);

  int even = 0, odd = 0, zero = 0, unknown = 0;
  for (int i = 1; i <= N; i += 1) {
    int num;
    printf("Enter number: ");
    if (scanf(" %d", &num) != 1) {
      unknown += 1;
    } else {
      switch(num%2) {
        case 0:
          even += 1; 
          if (num == 0) {
            zero += 1;
          }
          break;
        case 1:
        case -1:
          odd += 1; break;
      }
    }
  }
  printf("There are %d zero, %d even, %d odd, %d unknown valued numbers\n", 
          zero, even, odd, unknown);

  return 0;
}