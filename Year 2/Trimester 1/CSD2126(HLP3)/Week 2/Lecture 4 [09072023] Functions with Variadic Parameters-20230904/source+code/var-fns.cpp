// CSD2125/CS225 06/02/2022
// var-fns.cpp:
// illustration of facilities provided by standard C library <cstdarg>
// to implement C-style variadic functions [functions with varying parameters].

#include <iostream>
#include <cstdarg>

// declaring variadic function foo that takes one defined parameter and zero or more 
double foo(int param, ...) {
  va_list argp; // define argp to be of type variable parameter list
  va_start(argp, param); // assign to argp the address of first defined parameter param

  double ret_val{};
	
	// if user passes first defined parameter param to have zero value, then
	// there are no further parameters ...
  if (param == 0) {
    return ret_val;
  }
  
	// if user specifies first defined parameter to be odd value there will
	// be three parameters of type double; otherwise, there will be three parameter of type int
  if (param%2) { // defined param is odd, we get 3 doubles
    ret_val += va_arg(argp, double); // call va_arg to get each of the 3 double parameters, in turn
    ret_val += va_arg(argp, double);
    ret_val += va_arg(argp, double);
  } else { // defined param is even, we get 3 ints
    ret_val += va_arg(argp, int); // call va_arg to get each of the 3 int parameters
    ret_val += va_arg(argp, int);
    ret_val += va_arg(argp, int);
  }
	// va_list, va_start, va_arg use global variables defined by the standard C library
	// we must call va_end to reset these global variables to their default value ...
  va_end(argp);
  return ret_val;
}

// driver program ...
int main() {
  std::cout << "foo(0):                " << foo(0) << "\n";
  std::cout << "foo(0, 1, 2, 3):       " << foo(2, 1, 2, 3) << "\n";
  std::cout << "foo(1, 1.1, 2.2, 3.3): " << foo(1, 1.1, 2.2, 3.3) << "\n";
}
