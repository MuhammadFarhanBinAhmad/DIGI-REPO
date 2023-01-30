/*
* sentinel-avg.c - source file illustrating the use of a while loop where
* the loop control variable is checked against a sentinel value.
* What is a sentinel value? A sentinel value is a special value that can
* the loop control variable can be tested against to evaluate the
* while expression.
* Suppose you want to read some positive numbers and average them, but 
* you don't have a preset number of data items in mind. Suppose the number 
* -999 marks the end of the data. You evaluate the loop control variable
* against this sentinel value and continue with the iteration only if the
* loop control variable is not equivalent to this sentinel value.
*
* Input from standard input: sequence of integer values with final value
* equal to the sentinel value.
* Side effect of program: Write average of integer values read from 
* standard input.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror sentinel-avg.c -o sentinel-avg.out
*
* Run: ./sentinel-avg.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

// read integer values from standard input until sentinel value
// is read and return the average value of these integer values
// not including the sentinel value.
double average(int sentinel);

int main(void) {
  printf("Enter the sentinel integer: ");
  int sentinel_value;
  scanf("%d", &sentinel_value);

  printf("Average value: %.2f\n", average(sentinel_value));
  return 0;
}

/*
Sentinel-controlled while loop that computes the average value of a 
user-defined set of integer values read from standard input.
The sentinel value is the final value entered by the user.
*/
double average(int sentinel_value) {
  printf("Enter integers with final value equivalent to %d: ", sentinel_value);

  // read first number outside the loop
  int value;
  scanf("%d", &value);
  int count = 0, sum = 0;
  while (value != sentinel_value) {
    sum += value;
    count += 1;
    scanf("%d", &value);
  }
  return (double)sum/count;
}
