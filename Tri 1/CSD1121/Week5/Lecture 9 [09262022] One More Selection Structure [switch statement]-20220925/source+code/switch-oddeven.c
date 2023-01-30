/*
* switch-oddeven.c - source file illustrating the switch statement to print
* whether a number is even or odd.
*
* Input from standard input: Integer. Use CTRL-D combo to quit the program.
* Side effect of program: Print whether integer is odd or even.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror switch-oddeven.c -o switch-oddeven.out
*
* Run: ./switch-oddeven.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>
void odd_or_even(int); // function to print whether number is odd or even

int main(void) {
  while (1) {
    printf("Enter a positive integer: ");
    int value;
    if (scanf("%d", &value) != 1) {
      printf("Shutting down program ...\n");
      break;
    }
    odd_or_even(value);
  }
  
  return 0;
}

/*
This example shows how to execute the same statements for a group of values. 
*/
void odd_or_even(int num) {
  switch (num % 10) {
    case 0:
    case 2: 
    case 4:
    case 6:
    case 8: printf("%d is even\n", num); break;

    case 1:
    case 3: 
    case 5:
    case 7:
    case 9: printf("%d is odd\n", num); break;  
  }
}
