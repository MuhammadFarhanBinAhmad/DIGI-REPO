// pghali for HLP3
// 08/30/2022
// We want to create a C program with a main() defined in C that calls C functions
// [add() and mul()] and C++ function [draw_line()]. However, run-time C++ has
// initialization protocols for constructing C++ static objects [such as std::cin
// and std::cout]. Therefore, creating a mixed C/C++ program with a C main() is a
// bad idea and will not work in many situations. Therefore, we must rename C's
// main() to real_main() which will be called by a C++ main(). This C++ main will
// be the entry point to the mixed program which will enable the initialization of
// C++ static objects followed by a call to C's main() [now renamed as real_main()].
//
// Compile this C source file [with main() renamed as real_main()]:
// gcc -std=c11 -pedantic <additional warning flags> -c main-c.c

#include <stdio.h>
#include "drawline.hpp"
#include "calc.h"

int real_main(void) {
  int x = 10, y = 20;
  printf("%d | %d | %d\n", draw_line(x, y), add(x, y), mul(x, y));
  return 0;
}
