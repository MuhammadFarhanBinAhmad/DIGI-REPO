// HLP2: div-rem.cpp
// 01/24/2022
// The following code illustrates the use of type std::pair to return two values
// from a function.
// In C, we've to use pointer parameters to specify "in/out" values.
// In C++, we use reference parameters to specify "in/out" values.
// Since we can use class std::pair to treat two values as a single value, we
// can now replace two "in/out" reference parameters with a single value that
// is returned by a value of type std::pair.

#include <iostream>
#include <utility>

// Usual way to return more than two values in C/C++ is to either use
// two "in/out" reference parameters or one "in/out" reference parameter
// and one function return value ...
void divide_remainder(int dividend, int divisor, int& q, int& r) {
  q = dividend/divisor;
  r = dividend - divisor*q;
}

// A 2nd overload of divide_remainder: here we return both the quotient
// and remainder as a pair of values.
// Remember that returning values in modern C++ is inexpensive ...
std::pair<int, int> divide_remainder(int dividend, int divisor) {
  int quotient = dividend/divisor;
  int remainder = dividend - divisor*quotient;

  // can return the necessary std::pair<int,int> value in either
  // of two ways:
  //return std::pair<int,int> {quotient, remainder};
  return std::make_pair(quotient, remainder);
}

int main() {
  // make call to function returning multiple values using "in/out" reference parameters ...
  int q, r;
  divide_remainder(7, 3, q, r);
  std::cout << "quotient: "  << q << " | " << "remainder: " << r << '\n';

  // make call to overload of function divide_remainder that eschews "in/out"
  // reference parameters and instead returns the pair of quotient and
  // remainder as a single value ...
  std::pair<int, int> dr = divide_remainder(7, 3);
  std::cout << "quotient: "  << std::get<0>(dr) 
            << " | " << "remainder: " << std::get<1>(dr) << '\n'; 
}
