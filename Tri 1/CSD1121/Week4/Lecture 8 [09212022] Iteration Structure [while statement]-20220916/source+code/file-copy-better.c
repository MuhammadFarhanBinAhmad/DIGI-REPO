/*
* file-copy-better.c - source file illustrating the use of C standard library
* I/O functions getchar and putchar and a while loop to implement file copy
* by copying its input to its output one character at a time.
*
* Input from standard input: sequence of characters
* Side effect of program: Echo each character back to standard output.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror file-copy-better.c -o file-copy-better.out
*
* Run: ./file-copy-better.out < input-file > output-file
* with output-file being a copy of input-file
*
* The program can also be run so that users can enter characters in standard
* input and use the CTRL-D cobmo to signal End-of-File (EOF):
* Run: ./file-copy-better.out  
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

int main(void) {
  /*
  The expression ch = getchar() has a value which is the value written to the
  left operand ch. This means that an assignment expression can appear as part
  of a larger expression. Thus, we move the assignment to the test expression
  of the while loop.

  Inside the while expression, a character is read from stdin, assigned to ch
  and then tested to determine if its end-of-file signal. If the character is 
  not end-of-file, the body of the while loop is executed - printing the 
  previously read character to stdout.
  The while loop then repeats. When the end of input is finally reached,
  the while terminates.
  */
  int ch;
  while ( (ch = getchar()) != EOF ) {
    putchar(ch);
  }
  
  return 0;
}
