// HLP1 09/10/2016
// fc-char.c: use getc() and putc() to implement a file copy program.
// compile: gcc -std=c11 -pedantic-errors -Wall -Wextra -Werror fc-char2.c
// use: ./a.out
// check by running diff on the two files: diff theduck.txt thenewduck.txt

#include <stdio.h>

int main(void) {
  int ch; // must be an int!!!
  FILE *in = fopen("theduck.txt", "r");
  if (!in) {
    fputs("Unable to open theduck.txt!!!\n", stdout);
    return 0;
  } 
  FILE *out = fopen("thenewduck.txt", "w");
  if (!out) {
    fputs("Unable to open thenewduck.txt!!!\n", stdout);
    return 0;
  }

  while ( (ch = getc(in)) != EOF ) {
    putc(ch, out);
  }

  fclose(in); fclose(out);
  return 0;
}
