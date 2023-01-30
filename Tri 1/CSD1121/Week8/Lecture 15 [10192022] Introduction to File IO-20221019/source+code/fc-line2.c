// HLP1 09/10/2016
// fc-line2.c: use fgets() and fputs() to implement a file copy program.
// compile: gcc -std=c11 -pedantic-errors -Wall -Wextra -Werror fc-line.c
// use: ./a.out

#include <stdio.h>

int main(void) {
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

  char line[256];
  while (fgets(line, 256, in) != NULL) {
    fputs(line, out);
  }

  fclose(in); fclose(out);
  return 0;
}
