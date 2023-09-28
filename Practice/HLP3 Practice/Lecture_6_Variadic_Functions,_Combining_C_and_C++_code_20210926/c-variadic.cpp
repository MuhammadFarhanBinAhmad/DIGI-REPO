// illustration of facilities provided by standard C library <cstdarg>
// to implement C-style variadic functions.
// CSD2125
// 09/21/2021

#include <iostream>
#include <cstdarg>

// declaring variadic function foo that takes one defined parameter
// and zero or more 

double foo(int param, ...) {
  va_list argp;
  va_start(argp, param);

  double ret_val{};

  if (param == 0) {
    return ret_val;
  }
  
  if (param%2) { // defined param is odd, we get 3 doubles
    ret_val += va_arg(argp, double);
    ret_val += va_arg(argp, double);
    ret_val += va_arg(argp, double);
  } else { // defined param is even, we get 3 ints
    ret_val += va_arg(argp, int);
    ret_val += va_arg(argp, int);
    ret_val += va_arg(argp, int);
  }
  va_end(argp);
  return ret_val;
}

int main() {
  std::cout << "foo(0):                " << foo(0) << "\n";
  std::cout << "foo(0, 1, 2, 3):       " << foo(2, 1, 2, 3) << "\n";
  std::cout << "foo(1, 1.1, 2.2, 3.3): " << foo(1, 1.1, 2.2, 3.3) << "\n";
}
