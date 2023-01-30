/*
* fabs.c - source file defining and exercising following functions:
* 1. fabs_if for computing absolute value of a double-precision 
* floating-point value using if statement.
* 2. abs_if_int for computing absolute value of an int  
* value using if statement.
*
* Input from standard input:
* 1. double-precision floating-point number
* 2. integral values of type int
*
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

// function prototypes
double fabs_if(double);
int abs_if_int(int);

int main(void) {
  printf("Enter a double-precision floating-point number: ");
  double dval;
  scanf("%lf", &dval);
  printf("Absolute value of %f is: %f\n", dval, fabs_if(dval));
  
  printf("Enter another double-precision floating-point number: ");
  scanf("%lf", &dval);
  printf("Absolute value of %f is: %f\n", dval, fabs_if(dval));

  printf("Enter one more double-precision floating-point number: ");
  scanf("%lf", &dval);
  printf("Absolute value of %f is: %f\n", dval, fabs_if(dval));

  printf("Enter an integral value of type int: ");
  int int_val;
  scanf("%d", &int_val);
  printf("Absolute value of %d is: %d\n", int_val, abs_if_int(int_val));
  
  printf("Enter another an integral value of type int: ");
  scanf("%d", &int_val);
  printf("Absolute value of %d is: %d\n", int_val, abs_if_int(int_val));

  printf("Enter one more double-precision floating-point number: ");
  scanf("%d", &int_val);
  printf("Absolute value of %d is: %d\n", int_val, abs_if_int(int_val));
  
  return 0;
}

// Definition of function fabs_if using if statement
double fabs_if(double x) {
  if (x < 0.0) {
    x = -x;
  }
  return x;
}

// Definition of function abs_if_int using if statement
int abs_if_int(int x) {
  if (0 > x) {
    x = -x;
  }
  return x;
}
