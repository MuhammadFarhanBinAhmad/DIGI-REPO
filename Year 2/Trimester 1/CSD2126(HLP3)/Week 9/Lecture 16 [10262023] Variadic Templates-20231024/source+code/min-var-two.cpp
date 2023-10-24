// CSD2125/CS225 10/27
// min-var-two.cpp
// Function Min in source file min-var-one.cpp is a variadic function
// specific to int parameters. C++ allows the possibility of combining
// the specific feature of the C standard library [variadic functions]
// with a specific feature of the C++ programming language [function templates]
// to author a function that computes the minimum parameter from an unknown
// number of parameters as long as all the parameters are of the same type!!!
// What is to be done if the defined parameter count is zero? We simplify
// the design by requiring clients to ensure count is a positive value
// and that the function is called with the required number of parameters ...

#include <cstdarg>
// #include <limits> Not used anymore!!!
#include <iostream>

template <typename T>
T Min(int count, ...) {  
  va_list args; // define data structure to extract necessary parameter from stack frame ...
  va_start(args, count); // initialize args to extract parameter after parameter count
  // extract the 1st of the unspecified number of parameters of type T ...
  // if count is zero, return largest possible int value as minimum int value ...
  T min_val = va_arg(args, T);
  for (int i{1}; i < count; ++i) {
    // extract the next unspecified parameter of type T ...
    T val = va_arg(args, T);
    min_val = val < min_val ? val : min_val;
  }
  // clean up to ensure static variables are reset ...
  va_end(args);
  return min_val;
}

int main() {
  std::cout << Min<int>(1, -1) << "\n";
  //std::cout << Min<float>(1.f, -1.f) << "\n"; // bad call
  //std::cout << Min<short>(1, -1) << "\n";     // bad call
  std::cout << Min<double>(3, -2.2, -4.4, -4.0) << "\n";
  std::cout << Min<int>(4, -4, -3, -2, -6) << "\n";
}
