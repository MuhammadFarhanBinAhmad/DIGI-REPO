/*
* line-count.c - source file illustrating the use of while statement and the
* C standard library function getchar to count the number of lines in a file.
*
* Input from standard input: contents of text file redirected to standard input
* Side effect of program: Print number of lines in text file
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror line-count.c -o line-count.out
*
* Run: ./line-count.out < input-text-file
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

int main(void) {
/*
Recall that an input text stream is a sequence of lines;
each line has zero or more characters followed by newline ('\n') character.
Hence, counting lines in a text file is nothing but just counting newlines.
*/
  int line_counter = 0;
  int ch;
  while ((ch = getchar()) != EOF) {
/*
Conditional operator evaluation works like this:
1) expression (ch == '\n') is evaluated
2) if expression (ch == '\n') is true, then expression lc+1 is evaluated
and the result of the conditional expression is lc+1. Note that the third
expression is not evaluated.
3) if expression (ch == '\n') is false, then expression ln is evaluated
and the result of the conditional expression is lc. Note that the 2nd
expression is not evaluated.
*/
    line_counter = (ch == '\n') ? line_counter+1 : line_counter;
  }
  
  printf("line count: %d\n", line_counter);
  
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
