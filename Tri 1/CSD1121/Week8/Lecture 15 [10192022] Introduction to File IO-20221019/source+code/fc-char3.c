// HLP1 09/10/2016
// fc-char3.c: use fgetc() and fputc() to implement a file copy program.
// compile: gcc -std=c11 -pedantic-errors -Wall -Wextra -Werror fc-char3.c
// use: ./a.out 
// check by running diff on the two files: diff theduck.txt thenewduck.txt

#include <stdio.h>

int main(void) {
  int ch; // must be an int!!!
  FILE *in = fopen("theduck.txt", "r");//read only
  if (!in) {
    fputs("Unable to open theduck.txt!!!\n", stdout);
    return 0;
  } 
  FILE *out = fopen("thenewduck.txt", "w");//write. If file dont exist, will create one for you
  if (!out) {
    fputs("Unable to open thenewduck.txt!!!\n", stdout);
    return 0;
  }

  //put texts that in theduck into thenewduck
  while ( (ch = fgetc(in)) != EOF ) {
    fputc(ch, out);
  }

  fclose(in); fclose(out);
  return 0;
}
