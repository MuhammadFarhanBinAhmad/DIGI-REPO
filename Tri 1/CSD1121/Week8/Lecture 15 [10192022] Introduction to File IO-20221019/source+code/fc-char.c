// HLP1 09/10/2016
// fc-char.c: use getchar() and putchar() to implement a file copy program.
// compile: gcc -std=c11 -pedantic-errors -Wall -Wextra -Werror fc-char.c
// use: ./a.out < fc-char.c > fc-char2.c

#include <stdio.h>

int main(void) {
  int ch; // must be an int!!!
  while ( (ch = getchar()) != EOF ) {
    putchar(ch);
  }
  return 0;
}
