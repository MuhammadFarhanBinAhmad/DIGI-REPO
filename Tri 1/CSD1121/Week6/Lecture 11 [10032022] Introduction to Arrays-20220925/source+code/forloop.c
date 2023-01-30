/*
* forloop.c - source file illustrating for iteration statement that
* modifies arbitrarily large arrays.
*
* Input from standard input: None
* Side effect of program: Print pretty output of the first 40
* numbers in Fibonnaci sequence.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror 
            forloop.c -o forloop.out
*
* Run: ./forloop.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

/*
With the ability to define arrays, the next logical step is to construct
loops that modify arbitrarily large arrays.
The Fibonacci sequence is defined as follows. The first two elements of the
sequence are 1; the subsequent elements are defined as the sum of their two
predecessors: 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
*/

/*
#define SIZE 40 defines SIZE to be a synonym for 40.
The use of #define allows us to write code that is parameterized by a small
set of constants. If we ever want to change a parameter, we need only
change its definition. In this case, changing #define SIZE 40 to
#define SIZE 200 is simpler than changing every occurrence of 40 throughout
the code. More importantly, changing one line of code is less likely to
introduce bugs than changing many lines of code.
*/
#define SIZE 40

int main(void) {
  // define an array of SIZE integers and initialize the first two
  // elements to 1 and 1 and the remaining elements to 0
  unsigned int fib[SIZE] = {1, 1};

  /*
  specify the remaining elements up to the SIZE-th.
  Notice that fib is indexed from 0 to SIZE-1. In particular, the loop
  counter i ranges between 2 and SIZE-1, because the loop only executes
  while i < SIZE.
  Novice and even experienced programmers often introduce off-by-one bugs
  in which the loop condition is incorrectly written as i <= SIZE.
  Such errors can be insidious because one word beyond an array is typically
  still within the program's allotted memory. Thus, rather than causing a
  clean segmentation fault, the bug causes memory corruption which can be
  frustrating to identify and correct.
  */
  for (int i = 2; i < SIZE; ++i) {
    fib[i] = fib[i-2] + fib[i-1];
  }

  // print a pretty table of Fibonacci sequence with 5 columns ...
  printf("First %d elements of Fibonacci sequence:\n", SIZE);
  for (int i = 0; i < SIZE; ++i) {
    printf("%-10u", fib[i]);
    if (i && ((i+1)%5 == 0)) printf("\n");
  }
  
  return 0;
}
