// HLP2 05/26/2020
// fp-intro3.cpp:
// Same content as fp-intro.cpp except all functions are declared and
// defined using C++11 trailing return type syntax and we use the
// C++11 using keyword to provide alias to complicated declarations!!!

#include <iostream>

// nothing but declarations ...
auto square(int) -> int;
auto cube(int) -> int;
auto nth_power(int) -> int;

auto sum(int, int) -> int;
auto product(int, int) -> int;

auto main() -> int {
  // fp is a pointer to a function that takes an int parameter and returns an int value
  //int (*fp)(int) {square};
  // PTR_FUNC_INT is an alias for type "pointer to function taking an int and returning an int"
  using PTR_FUNC_INT = auto (*)(int) -> int;
  PTR_FUNC_INT fp {square};
  
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
  //int (*fp2)(int, int) = sum;
  auto (*fp2)(int,int) -> int {sum};
  std::cout << "3 * (4 + 5) + 6 = " << fp2(product(3, fp2(4, 5)), 6) << '\n';
}

// these are not only declarations but also definitions ...
auto sum(int x, int y) -> int { 
  return x+y;
}

auto product(int x, int y) -> int  {
  return x*y;
}

auto square(int x) -> int {
  return x*x;
}

auto cube(int x) -> int {
  return x*x*x;
}

auto nth_power(int n) -> int {
  int value {1};
  for (int i{1}; i <= n; ++i) {
    value *= n;
  }
  return value;
}
