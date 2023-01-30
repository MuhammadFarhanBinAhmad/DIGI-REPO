/*
* pass-or-fail.c - source file containing function fabs_if for computing the 
* absolute value of a floating-point value using the if statement.
*
* Input from standard input: floating-point number
* Side effect of program: Compute and write absolute value of user-supplied
* floating-point value of type double to standard output
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror fabs.c -o fabs.out
*
* Run: ./fabs.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

// function declarations
char pass_or_fail(double);
char pass_or_fail_v2(double);
char pass_or_fail_v3(double);

int main(void) {
  printf("Enter your grade: ");
  double val;
  scanf("%lf", &val);
  
  printf("Score: %f | letter grade: %c\n", val, pass_or_fail(val));
  printf("Score: %f | letter grade: %c\n", val, pass_or_fail_v2(val));
  printf("Score: %f | letter grade: %c\n", val, pass_or_fail_v3(val));
  
  return 0;
}

// first pass ... using if statement with else clause
char pass_or_fail(double grade) {
  char ltr_grade;
  
  if (grade >= 70.0) {
    ltr_grade = 'P';
  } else { 
    ltr_grade = 'F';
  }
  return ltr_grade;
}

// second pass ... using if statement with else clause without
// the need for a local variable
char pass_or_fail_v2(double grade) {
  if (grade >= 70.0) {
    return 'P';
  } else {
    return 'F';
  }
}

// best implementation that replaces the if statement with else
// clause with the conditional operator
char pass_or_fail_v3(double grade) {
  /*
  this is the ternary condition operator which has the form:
  
  expr1 ? expr2 : expr3
  
  where expr1, expr2 and expr3 are expressions of any type.
  The expression evaluates as:
  if expr1 is true, then result of expression is expr2; otherwise
  result of expression is expr3.
  This is similar to the if-else construct:
  
  if (expr1)
    expr2;
  else
    expr3;
  */
  return (grade >= 70.0) ? 'P' : 'F';
}
