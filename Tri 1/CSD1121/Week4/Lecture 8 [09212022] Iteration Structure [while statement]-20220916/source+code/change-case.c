/*
* change-case.c - source file containing function to_upper for converting
* lower-case characters to upper-case.
*
* Input from standard input: sequence of characters
* Side effect of program: Echo characters read from stdin to stdout while
* converting lower-case characters to upper-case.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror change-case.c -o change-case.out
*
* Run: ./change-case.out < input.txt > output.txt
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // getchar, putchar

/*
Function converts lower-case Latin characters to upper-case. The function
relies on the fact that lower- and upper-cased Latin characters are
encoded (say in ASCII or any other encoding scheme) such that the integer
values for lower-case characters are in increasing order.
It is also assumed that upper-case Latin characters are also encoded with
integer values in increasing order from 'A' to 'Z'. 
*/
int to_lower(int ch) {
  return ('a' <= ch && ch <= 'z') ? ch-'a'+'A' : ch;
}

int main(void) {
  int ch;

  while ( (ch = getchar()) != EOF ) {
    putchar(to_lower(ch));
  }
  return 0;
}
