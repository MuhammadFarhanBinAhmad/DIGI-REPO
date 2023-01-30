/*
* fabs-cond-oper.c - source file containing C code for illustrating 
* conditional operator and conditional expression.
* This is done by implementing functions that return the absolute value
* of a floating-point value of type double.
* Functions fabs_if uses the if statement to return the absolute value,
* while function fabs_cond_oper returns the absolute value using 
* conditional operator.
* See the definition of the fabs_cond_oper for an explanation of the
* conditional operator.
*
* Input from standard input: floating-point number
* Side effect of program: Compute and write absolute value of user-supplied
* floating-point value of type double to standard output
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror fabs-cond-oper.c -o fabs-cond-oper.out
*
* Run: ./fabs-cond-oper.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

// function prototypes
double fabs_if(double);
double fabs_cond_oper(double);

int main(void) {
  double val, abs_val;
  
  printf("Enter a floating-point number: ");
  scanf("%lf", &val);
  
  abs_val = fabs_if(val);
  printf("Absolute value of %f is: %f (using fabs_if)\n", val, abs_val);
  
  abs_val = fabs_cond_oper(val);
  printf("Absolute value of %f is: %f (using fabs_cond_oper)\n", val, abs_val);
  
  return 0;
}

/*
Definition of function fabs_if using if statement.
*/
double fabs_if(double x) {
  if (x < 0.0) {
    x = -x;
  }
  return x;
}

/*
Definition of function fabs_cond_oper using conditional operator.

The conditional operator consists of symbols ? and : which must be used
together in the following way:

    expr1 ? expr2 : expr3

where expr1, expr2, and expr3 can be expressions of any type.
The conditional operator requires 3 operands and is therefore the only
ternary operator in C/C++.
It has lower precedence than other operators except the assignment and comma
comma operator and is right-associative.

The expression resulting from using a conditional operator is called a 
conditional expression.
Execution of conditional expression expr1 ? expr2 : exp3 proceeds as follows:
1) expr1 is fully evaluated and tested against zero.
2) If expr1 is not equal to zero, then expr2 is evaluated and its value,
   converted to the result type, becomes value of conditional expression.
   Note that expr3 is not evaluated.
3) If expr1 is equal to zero, then expr3 is evaluated and its value, converted
   to the result type, becomes the value of conditional expression. 
   Note that expr2 is not evaluated.

Therefore, expression r = a ? b : c is equivalent to:

  if (a) {
    r = b;
  } else {
    r = c;
  }

The conditional operator is always a better alternative to the if statement
for the following reasons:
1) the conditional operator reads better. Humans can easily understand the 
   single-line implementation of conditional operator versus the multi-line
   text of an if statement).
2) in some cases, the compiler can translate the conditional operator to a
   CPU instructor, thereby allowing for faster execution of the selection
   structure.
*/
double fabs_cond_oper(double x) {
  return (x < 0.0) ? -x : x;
}
