/*
* lisa.c - source file illustrating the use of while loop to print a greeting
* multiple times to standard output.
*
* Input from standard input: integer number specifying how many times to
* print greeting to standard output.
* Side effect of program: Write greeting to standard output using a
* counter-controlled while statement.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror lisa.c -o lisa.out
*
* Run: ./lisa.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

int main(void) {
  printf("Enter number of times you want to greet: ");
  int max_cnt; // maximum number of repetitions
  scanf("%d", &max_cnt);
  
  /*
  We'd like to print a message to the screen a specified number of times
  given by variable max_cnt.
  The loop uses a variable known as a counter variable or simply counter,
  to store the number of iterations that have been performed.
  In our example, the counter variable is ctr.
  Using the counter (ctr), the loop typically performs the following actions:
  initialization, test, and increment.
  
  1) Initialization: Before the loop begins, the counter (ctr) is initialized
  to starting value 0. The starting value depends on the particular situation.
  2) Test: The loop tests the counter (ctr) by comparing it to a maximum value
  given by max_cnt. If the expression evaluates true (ctr is less than 
  max_cnt), the body of the loop (that is, the 3 statements enclosed in braces)
  is executed. If ctr is greater than or equal to max_cnt, the loop terminates,
  and execution continues at the statement that follows the loop.
  3) Increment: To increment a variable means to increase a value. During each 
  iteration, the loop increments the counter (ctr) by adding 1 to it.
  */
  
  int ctr = 0; // initialize counter variable 
  while (ctr < max_cnt) { // test expression (ctr < max_cnt) 
    printf("Lisa Simpson is cool!!! ");
    ctr += 1;             // increment counter variable 
    printf("Value of incremented counter: %d\n", ctr);
  }
  
  return 0;
}
