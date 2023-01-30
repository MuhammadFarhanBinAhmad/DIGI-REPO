/*
* counter-avg.c - source file illustrating a counter-controlled while loop
* that computes the average value of a user-defined set of integer values 
* read from standard input.
*
* Input from standard input: integer number specifying total number of integer
* values to read followed by these many integers.
* Side effect of program: Write average of integer values read from 
* standard input.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror counter-avg.c -o counter-avg.out
*
* Run: ./counter-avg.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

// read N integer values from standard input and return their average value
double average(int N);

int main(void) {
  printf("Enter number of values to read: ");
  int N;
  scanf(" %d", &N);
  printf("Average is %.2f\n", average(N));
  return 0;
}

/*
Counter-controlled while loop that computes the average value of a 
user-defined set of integer values read from standard input.
*/
double average(int N) {
  printf("Enter %d integers\n", N);
  int counter = 0, sum = 0;
  while (counter < N) {
    int temp;
    scanf(" %d", &temp);
    sum += temp;
    counter += 1;
  }
  return (double)sum/N;
}
