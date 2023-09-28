// CSD2125 11/09
// part of program to show that lambdas can be used to
// replace C style functions ...
// this source file defines functions declared in calc.h
// that are callable by both C and C++ functions ...
// compile (only) like this: gcc -std=c11 -c calc.c
#include "calc.h"

bool fun_max(int lhs, int rhs) {
  return lhs > rhs;
}

bool fun_min(int lhs, int rhs) {
  return lhs < rhs;
}

bool compare(int lhs, int rhs, bool (*func_ptr)(int, int)) {
  return func_ptr(lhs, rhs);
}
