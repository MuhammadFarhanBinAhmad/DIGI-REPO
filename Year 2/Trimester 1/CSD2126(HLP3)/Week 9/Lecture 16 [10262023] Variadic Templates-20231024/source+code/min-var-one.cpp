// CSD2125/CS225 10/27/2022
// min-var-one.cpp
// Function Min illustrates the use of C standard library macros declared in
// <cstdarg> to find the minimum value from a variable number of int arguments.
// The number of arguments is specifed by the defined [that is, first] parameter ...

#include <cstdarg>
#include <limits>
#include <iostream>

int Min(int count, ...) {  
  va_list args; // define data structure to extract necessary parameter from stack frame ...
  va_start(args, count); // initialize args to extract parameter after parameter count

  // if count is zero, return largest possible int value as minimum int value ...
  int min_val = std::numeric_limits<int>::max();

  for (int i{}; i < count; ++i) {
    // extract the next int parameter ...
    int val = va_arg(args, int);
    min_val = val < min_val ? val : min_val;
  }
  // clean up to ensure static variables are reset ...
  va_end(args);
  return min_val;
}

int main() {
  std::cout << Min(0) << "\n";
  std::cout << Min(1, -1) << "\n";
  std::cout << Min(3, -2, -3, -4) << "\n";
  std::cout << Min(3, -4, -3, -2) << "\n";
  std::cout << Min(3, -3, -4, -2) << "\n";
}