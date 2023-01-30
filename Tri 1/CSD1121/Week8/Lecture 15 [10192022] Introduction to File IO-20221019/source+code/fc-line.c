// HLP1 09/10/2016
// fc-line.c: use fgets() and fputs() to implement a file copy program.
// compile: gcc -std=c11 -pedantic-errors -Wall -Wextra -Werror fc-line.c
// use: ./a.out < theduck.txt > thenewduck.txt

#include <stdio.h>
#include <string.h>
int main(void) {
  char line[256];
  //(fgets(line, 256, stdin));//get only 256 char
  while (fgets(line, 256, stdin) != NULL) {
    fputs(line, stdout);
    fputc('\n', stdout);
    printf("%ld",strlen(line));
  }
  return 0;
}
