// HLP2 05/26/2020
// fp-intro.cpp:
// Function pointers:
//  - Syntax for defining function pointers
//  - Using a function pointer to indirectly call a function

#include <iostream>

// nothing but declarations ...
int square(int);
int cube(int);
int nth_power(int);

int sum(int, int);
int product(int, int);

int main() {
  // fp is a pointer to a function that takes an int parameter and returns an int value
  int (*fp)(int) {square};
  std::cout << "sizeof(function pointer): " << sizeof(fp) << " | "
            << "sizeof(int*): " << sizeof(int*) << '\n';

  int value {5};
  // directly call function square ...
  std::cout << "direct call to square:   " << square(value) << '\n';
  // indirectly call function square thro' function pointer fp ...
  std::cout << "indirect call to square: " << (*fp)(value)  << '\n';
  std::cout << "indirect call to square: " << fp(value)     << '\n';

  std::cout << "Enter a positive integer value: ";
  std::cin >> value;
  // some users don't follow explicit instructions ...
  value = value < 0 ? -value : value;
  // if value is an even value, make fp point to function cube;
  // otherwise make fp point to function nth_power
  fp = value % 2 ? cube : nth_power;
  // call either function cube or function nth indirectly thro' fp ...
  std::cout << "calling a function indirectly thro' fp: " << (*fp)(5) << '\n';

  // ludicrously convoluted expression to do some simple arithmetic!!!
  int (*fp2)(int, int) = sum;
  std::cout << "3 * (4 + 5) + 6 = " << fp2(product(3, fp2(4, 5)), 6) << '\n';
}

// these are not only declarations but also definitions ...
int sum(int x, int y) { return x+y; }
int product(int x, int y)  { return x*y; }
int square(int x) { return x*x; }
int cube(int x)   { return x*x*x; }
int nth_power(int n) {
  int value {1};
  for (int i{1}; i <= n; ++i) {
    value *= n;
  }
  return value;
}
