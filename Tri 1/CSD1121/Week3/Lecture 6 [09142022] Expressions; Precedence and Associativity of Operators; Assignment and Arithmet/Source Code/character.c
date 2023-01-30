#include <stdio.h>

/*
* character.c - source file containing C code for illustrating
* char variables and character constants.
*
* Input from standard input: None
* Side effect: Print integer values of certain character constants.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror character.c -o character.out
*
* Run: ./character.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
int main(void) {
  char ch;
  ch = 'A';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = 'X';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = 'a';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = 'e';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = '+';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = '0';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = '9';  printf("ch: %c | ch: %x\n", ch, ch);
  ch = '\n'; printf("ch: %c | ch: %x\n", ch, ch);

  int ich;
  ich = 'A';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = 'X';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = 'a';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = 'e';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = '+';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = '0';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = '9';  printf("ich: %c | ch: %x\n", ich, ich);
  ich = '\n'; printf("ich: %c | ch: %x\n", ich, ich);

  
  return 0;
  
}
