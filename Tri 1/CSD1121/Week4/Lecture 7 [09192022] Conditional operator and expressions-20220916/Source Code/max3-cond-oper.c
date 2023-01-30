/*
* max3-cond-oper.c - source file containing C code for illustrating 
* conditional operator and expressions resulting from this operator.
*
* Function max3_if_else returns the larger of three values using
* if statement with else clauses.
* Function max3_cond_oper is simply the version of max3_if_else rewritten
* to only use the conditional operator.
* Function max2 returns the larger of two values using conditional operator.
* Function max3_using_max2 returns the larger of three values by calling
* function max2 twice: once to compute the larger of first two values and
* then calling max2 again with the larger of first two values and the third
* value.
* selection structures
* using if statements. This is done by implementing functions that return the
* absolute value of a floating-point value of type double.
* Functions fabs uses the if statement, while function fabs_best uses the
* conditional operator.
* The conditional operator is always a better alternative to the if statement
* for the following reasons:
* 1) the conditional operator reads better. Humans can easily understand the 
* single-line implementation of conditional operator versus the multi-line text
* of an if statement).
* 2) in some cases, the compiler can translate the conditional operator to a
* CPU instructor, thereby allowing for faster execution of the selection
* structure.
*
* Input from standard input: floating-point number
* Side effect of program: Compute and write absolute value of user-supplied
* floating-point value of type double to standard output
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror max3-cond-oper.c -o max3-cond-oper.out
*
* Run: ./max3-cond-oper.out
* 
* Prasanna Ghali
* Original program written: 09/01/2020
* written for High-Level Programming I
*/

#include <stdio.h>

/*
Order three values x, y, and z in ascending or descending order.
*/
int max3_if_else(int x, int y, int z) {
  int max;

  if (x > y) { // x > y
    if (x > z) { // x >  z and x > y, so x is larger of x, y, and z
      max = x;
    } else {     // x <= z but x > y, so z is larger of x, y, and z
      max = z;
    }
  } else {     // x <= y
    if (y > z) { // y >  z and x <= y, so y is larger of x, y, and z
      max = y;
    } else {     // y <= z but x <= y, so z is larger of x, y, and z 
      max = z;
    }
  }
  return max;
}

/*
Order three values x, y, and z in ascending or descending order.
*/
int max3_cond_oper(int x, int y, int z) {
  int max = (x > y) ? (x > z ? x : z) : (y > z ? y : z) ;
  return max;
  // better:
  // return (x > y) ? (x > z ? x : z) : (y > z ? y : z) ;
}

/*
Return larger of two values x and y
*/
int max2_cond_oper(int x, int y) {
  return x > y ? x : y;
}

/*
Return larger of three values x, y, and z using function max2.
*/
int max3_using_max2(int x, int y, int z) {
  return max2_cond_oper(max2_cond_oper(x, y), z);
}

/*
Test the three different ways to find maximum of three values:
a) max3_if_else   (using the if statement with else clause)
b) max3_cond_oper (using only the conditional operator)
c) max3_using_max2 (using max2 - a function to find larger of 2 values -
                   where max2 is implemented using conditional operator)
*/
int main(void) {
  printf("Enter three integer values: ");
  int x, y, z;
  scanf("%d %d %d", &x, &y, &z);
  printf("Max of (%d, %d, %d) values is: %d, %d, %d\n", x, y, z, 
        max3_if_else(x, y, z), max3_cond_oper(x, y, z), max3_using_max2(x, y, z));

  printf("Enter three integer values: ");
  scanf("%d %d %d", &x, &y, &z);
  printf("Max of (%d, %d, %d) values is: %d, %d, %d\n", x, y, z, 
        max3_if_else(x, y, z), max3_cond_oper(x, y, z), max3_using_max2(x, y, z));

  printf("Enter three integer values: ");
  scanf("%d %d %d", &x, &y, &z);
  printf("Max of (%d, %d, %d) values is: %d, %d, %d\n", x, y, z, 
        max3_if_else(x, y, z), max3_cond_oper(x, y, z), max3_using_max2(x, y, z));

  printf("Enter three integer values: ");
  scanf("%d %d %d", &x, &y, &z);
  printf("Max of (%d, %d, %d) values is: %d, %d, %d\n", x, y, z, 
        max3_if_else(x, y, z), max3_cond_oper(x, y, z), max3_using_max2(x, y, z));

  return 0;
}
