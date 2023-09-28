// CSD2125 11/09
// part of program to show that lambdas can be used to
// replace C style functions ...
// compile and link with calc.o like this:
// gcc -std=c11 main.c calc.o -o c.out
#include <stdio.h>
#include "calc.h"

int main(void) {
  printf("fun_max(10, 20) returns %s\n", fun_max(10, 20) ? "true" : "false");
  printf("fun_min(10, 20) returns %s\n", fun_min(10, 20) ? "true" : "false");
  printf("compare(10, 20) returns %s\n", compare(10, 20, fun_max) ? "true" : "false");

  return 0;
}
