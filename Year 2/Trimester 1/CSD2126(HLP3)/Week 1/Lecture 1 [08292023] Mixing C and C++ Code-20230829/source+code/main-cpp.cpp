// pghali for HLP3
// 08/30/2022
// We wanted to create a C program with a main() defined in C that calls C
// functions [add() and mul()] and C++ function [draw_line()]. However, run-time
// C++ has initialization protocols for constructing C++ static objects [such as
// std::cin and std::cout]. Therefore, creating a mixed C/C++ program with a C 
// main() is a bad idea and will not work in many situations. Therefore, we must
// rename C's main() to real_main() which will be called by a C++ main(). This C++
// main will be the entry point  to the mixed program which will enable the 
// initialization of C++ static objects followed by a call to C's main() [now 
// renamed as real_main()].
// 
// Create a C++ source file main-cpp.cpp that will define main() which in turn
// will call C function real_main(). To avoid name mangling, we must use
// extern "C" directive with name real_main.
// To illustrate that C functions can be called by C++ functions, this C++ main()
// will call C functions add() and mul() that are declared in calc.h and defined
// in calc.o
// To illustrate that C++ function designed for C functions can also be called by
// C++ functions, main() will make a call to C++ function draw_line() that is
// defined in drawline.cpp.
// Compile C++ source file main-cpp.cpp:
// g++ -std=c++17 -pedantic <additional warning flags> -c main-cpp.cpp

#include <iostream>
#include "drawline.hpp"
#include "calc.h"

// Avoid name mangling for driver function defined in C source file ...
extern "C"
int real_main(void);

int main() {
  // calling C and C++ functions from C program:
  real_main();

  // calling C and C++ functions from C++ program
  int x{50}, y{10};
  std::cout << draw_line(x, y) << " | " << add(x, y) << " | " << mul(x, y) << "\n";
}
