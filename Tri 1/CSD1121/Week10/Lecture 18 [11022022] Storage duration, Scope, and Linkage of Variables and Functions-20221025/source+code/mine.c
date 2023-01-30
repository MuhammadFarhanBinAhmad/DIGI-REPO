#include <stdio.h> // declare function printf

/*
mine.c and yours.c compile and link.
At later point, author of mine.c wishes to use the functions
implemented in theirs.c
Each of the three files compile but they don't link because
mine.c and theirs.c break the one definition rule!!!
This is fixed by making the external variable in theirs.c
private to the functions in theirs.c.
*/

// declare (and define) external variable x with default external linkage
int x = 10;

int main(void) {
  // call function foo_in_your_file defined in file yours.c
  extern void foo_in_your_file(void);
  foo_in_your_file();
  printf("mine.c's x: %d\n", x);

  // compute some circle stuff ...
  #if 1
  extern double area(double);
  double radius = 2.0;
  printf("Area of circle with radius %.2f is: %.2f\n", radius, area(radius));
  #endif

  return 0;
}
