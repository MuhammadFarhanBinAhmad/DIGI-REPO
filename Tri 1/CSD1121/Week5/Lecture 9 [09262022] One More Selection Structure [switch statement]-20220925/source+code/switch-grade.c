/*
* switch-grade.c - source file illustrating the switch statement, the
* break statement, and using the scanf function to read values from
* input stream and ignore them. 
*
* Input from standard input: Characters representing grades.
* Side effect of program: Print grade(s)
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror switch-grade.c -o switch-grade.out
*
* Run: ./switch-grade.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>
void print_my_grade(char);

int main(void) {
  while (1) {
    printf("Enter your grade (P for Pass, F for Fail, Q to Quit): ");
    char ch;
    /*
    The asterisk indicates that the data is to be read
    from the stream but ignored
    */
    scanf("%c%*c", &ch);
    if (ch == 'Q') {
      /*
      The break statement in a iteration structure such as while or for loop 
      will cause program to immediately exit the iteration structure.
      Program execution will continue with the first statement following the
      iteration structure.
      */
      break;
    }
    print_my_grade(ch);
  }
  
  return 0;
}

/*
In addition to the if and if-else selection structures,
C provides the switch structure which gives the program
the ability to implement multi-way selections - that is,
the ability to choose from one of many alternatives.

The general format is:

switch(integral_expression) {
  case integral_value_1:
    statements_1
    break; // this is optional
  case integral_value_2:
    statements_2
    break; // this is optional
  .
  .
  .
  case integral_value_n:
    statements_n
    break; // this is optional
  default: // this is optional
    statements_default
}

The switch statement executes according to these rules:
1) When the value of integral_expression is matched against
a case value (also called a label), the statements executes
until either a break statement is encountered or the end of
the switch structure is reached.

2) If the value of integral_expression doesn't match any of
the case values, the statements following the default label
execute. If the switch statement doesn't have a default
label (and if the value of integral_expression doesn't match
any of the case values, the entire switch statement is skipped.

3) A break statement causes an immediate exit from the
switch structure.
*/
void print_my_grade(char ch) {
  switch(ch) {
    case 'P':
      printf("You passed!!!\n");
      break;
      
    case 'F':
      printf("Oh no - You failed!!!\n");
      break;
      
    default:
      printf("No such grade exists\n");
      break;
  }
}
