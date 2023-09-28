// CSD2125
// 09/23/2021
#include <iostream>
// We wish to import the C++ library declared in drawline.h and
// the C library declared in calc.h into the C++ project.
// To import these two libraries into the executable:
// 1) compile only with g++: g++ -std=c++17 <additional flags if you wish> -c main-cpp.cpp
// 2) link main-cpp.o with C++ library drawline.o and C library calc.o:
//    g++ main-cpp.o calc.o drawline.o -o cppland.out
#include "drawline.h"
#include "calc.h"

int main() {
  int x = 10, y = 20;
  std::cout << draw_line(x, y) << " | " << add(x, y) << " | " << mul(x, y) << "\n";
}
