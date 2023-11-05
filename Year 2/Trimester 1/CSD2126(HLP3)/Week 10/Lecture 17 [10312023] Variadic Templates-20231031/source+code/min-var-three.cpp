// CSD2125/CS225 10/27
// min-var-three.cpp
// There are several problems with function Min implemented in min-var-two.cpp:
// 1) We're using a variety of macros [va_list, va_start, va_arg, va_end] from
// the C standard library. As with all macros, they're not type-safe. For example,
// we cannot use the previous function Min for parameters of type short or
// parameters of type float because the C standard library promotes all integral
// variables of type short and type float to type int and type double, respectively.
// 2) Even though the compiler knows the number and types of parameters at compile-
// time, compilation only happens at run-time.
// 3) Functions must be provided the number of parameters - this happens in a
// variety of ways. For example, printf uses format specifiers in the format string
// to specify the types and numbers of additional parameters. The program would
// exhibit undefined behavior if fewer parameters are supplied than the number
// specified in the format string or if the types of the parameters don't match the
// parameters specified in the format string. Function Min [from min-var-two.cpp]
// requires a first parameter specifying the number of parameters from whom the
// minimum value is to be determined. The program would have undefined behavior if
// the number of additional parameters don't match the value specified in the first
// parameter.
// Variadic templates alleviate these problems:
// 1) They're evaluated at compile-time.
// 2) They're applicable to both functions and classes - this is quite
// useful in Modern C++ to implement type traits ...
// 3) They're type-safe and do not require macros.
// 4) C-style variadic functions require a defined argument but C++
//    variadic template functions don't need a defined argument ...

#include <iostream>
#include <string>

template <typename T>
T Min(T lhs, T rhs) {
  return lhs < rhs ? lhs : rhs;
}

// a pack of template parameters [type, non-type, template template]
// that are called template parameter pack are specified in the
// template parameter list like this: typename... Types
template <typename T, typename... Types>
// a pack of function parameters in the function parameter list,
// as in: Types... tail
T Min(T head, Types ... tail) {
  // function parameter pack tail is expanded in the function body,
  // like this: tail...
  // this is known as parameter pack expansion 
  // the result of a parameter pack expansion is a comma-separated list
  // of zero or more expressions.
  return Min(head, Min(tail...));
}

int main() {
  std::cout << "Min(1.1, -1.1, -2.2, 2.2, -3.3): "
            << Min(1.1, -1.1, -2.2, 2.2, -3.3) << "\n";
  /*
  the compiler will expand the call Min(1.1, -1.1, -2.2, 2.2, -3.3) into the call:
  Min(1.1, Min(-1.1, -2.2, 2.2, -3.3)) causing the following function to be
  instantiated:
  template <double, double, double, double, double>
  double Min(double head, double tail0, double tail1, double tail2, double tail3) {
    return Min(head, Min(tail0, tail1, tail2, tail3));
  }

  the argument Min(-1.1, -2.2, 2.2, -3.3) is expanded into the call:
  Min(-1.1, Min(-2.2, 2.2, -3.3)) causing the following function to be
  instantiated:
  template <double, double, double, double>
  double Min(double head, double tail0, double tail1, double tail2) {
    return Min(head, Min(tail0, tail1, tail2));
  }

  the argument Min(-2.2, 2.2, -3.3) is expanded into the call:
  Min(-2.2, Min(2.2, -3.3)) causing the following function to be
  instantiated:
  template <double, double, double>
  double Min(double head, double tail0, double tail1) {
    return Min(head, Min(tail0, tail1));
  }

  the argument Min(2.2, -3.3) causes the function
  template <double>
  double Min(double lhs, double rhs) {
    return lhs < rhs ? lhs : rhs;
  }

  }
  */
  

  std::cout << "Min(1, 2): " << Min(1, 2) << "\n";
  // does the following function call work?
  std::cout << "Min(\"hello\", \"world\"): " << Min("hello", "world") << "\n";
  // what about this call?
  std::cout << "Min(std::string(\"hello\"), std::string(\"world\")): " 
            << Min(std::string("hello"), std::string("world")) << "\n";

}
