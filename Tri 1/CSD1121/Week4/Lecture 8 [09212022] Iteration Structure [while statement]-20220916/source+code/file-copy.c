/*
* file-copy.c - source file illustrating the use of C standard library
* I/O functions getchar and putchar and a while loop to implement file copy
* by copying its input to its output one character at a time.
*
* Input from standard input: sequence of characters
* Side effect of program: Echo each character back to standard output.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror file-copy.c -o file-copy.out
*
* Run: ./file-copy.out < input-file > output-file
* with output-file being a copy of input-file
*
* The program can also be run so that users can enter characters in standard
* input and use the CTRL-D cobmo to signal End-of-File (EOF):
* Run: ./file-copy.out  
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

int main(void) {
  /*
  algorithm to implement file copy by copying its input to
  its output one character at a time:
  1) read a character
  2) while (character is not end-of-file indicator)
  3)    output the character read
  4)    read the next character
  */
  int ch = getchar(); // see below for why getchar() returns an int
  // != is relational operator means "not equal to"
  // use CTRL-D combo to signal to the program that end-of-file is reached
  // and no further characters will be input in the standard input stream
  while (ch != EOF) {
    putchar(ch);
    ch = getchar();
  }
  
  return 0;
}

/*
Why is getchar() being assigned to an int even though we're reading and writing
char's? The particular problem that getchar is trying to solve is how to 
distinguish the end of input from valid data. This requires that the end of 
input must be a value that cannot be confused with any real character. This 
value is called EOF - "end of file". Thus, we must declare ch to be a type big
enough to hold any value that getchar() returns. A char type wouldn't work 
since ch must hold all possible char's plus this EOF value.
Therefore, we use int.

EOF is a macro defined in <stdio.h> representing an integer value - the specific
value is irrelevant as long as it is not the same as any char value. By using the
macro EOF, we don't care about the specific value.
*/