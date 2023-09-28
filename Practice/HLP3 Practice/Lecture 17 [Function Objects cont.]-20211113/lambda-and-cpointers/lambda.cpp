// CSD2125 11/09
// C++ program to replace C function pointers with lambdas
// C functions fun_min, fun_max, and compare are declared in 
// "calc.h" and defined in calc.c
// compile (only) calc.c like this: gcc -std=c11 -c calc.c
// compile/link lambda.cpp and calc.o like this:
// g++ -std=c++17 lambda.cpp calc.o -o cpp.out
#include <iostream>
#include <string>
#include "calc.h" // for fun_min, fun_max, comp

int main() {
  int a = 10, b = 20, c = 15;

  // call C functions fun_min and fun_max ...
  std::cout << "fun_max: " << std::boolalpha << fun_max(10, 20) << "\n";
  std::cout << "fun_min: " << std::boolalpha << fun_min(10, 20) << "\n";

   // call C function comp using function pointers ...
  std::cout << "compare: " << std::boolalpha << compare(10, 20, fun_max) << "\n";
  std::cout << "compare: " << std::boolalpha << compare(10, 20, fun_min) << "\n";

  // define lambdas as replacements for C functions fun_min and fun_max
  // notice the + token to indicate that lambda is capture-less
  auto lam_max = +[](int lhs, int rhs) -> bool { return lhs > rhs; };
  auto lam_min = +[](int lhs, int rhs) -> bool { return lhs < rhs; };
  
  // test the two lambdas that don't capture ...
  std::cout << "lam_max: " << std::boolalpha << lam_max(10, 20) << "\n";
  std::cout << "lam_min: " << std::boolalpha << lam_min(10, 20) << "\n";

  // call C function comp using lambdas ...
  std::cout << "compare: " << std::boolalpha << compare(10, 20, lam_max) << "\n";
  std::cout << "compare: " << std::boolalpha << compare(10, 20, lam_min) << "\n";
}
