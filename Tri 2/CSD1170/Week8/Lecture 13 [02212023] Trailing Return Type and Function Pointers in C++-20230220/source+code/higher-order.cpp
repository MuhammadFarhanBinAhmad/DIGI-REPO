// HLP2 05/26/2020
// higher-order.cpp:
// Illustrates the use of function pointers as callback functions for
// higher-order functions
// A function passed to another function as an argument is referred to as a
// callback function, the function that accepts another function as a parameter
// is a higher-order function.
// This example showcases the tremendous value of higher-order functions and
// callbacks in the never-ending battle against code duplication ...

#include <iostream>
#include <string>
#include <vector>
#include <cstddef> // for size_t

// Higher-order function that calls the function that parameter compare points to.
// The caller of the find_optimum function determines what it means for one
// int value to be better or more optimal to the other.
// If it's the minimum element you want, you pass a comparision function
// equivalent to the less-than operator.
// If it's the maximum element, you want the compare callback to behave
// like the greater-than operator, and so on.
//const int* find_optimum(std::vector<int> const& values, bool compare(int,int)) {
//const int* find_optimum(std::vector<int> const& values, bool (*compare)(int, int)) {
const int* find_optimum(std::vector<int> const& values, auto compare(int,int) -> bool) {
  if (values.empty()) { return nullptr; }
  int const *optimum = &values[0];
  for (std::size_t i{1}; i < values.size(); ++i) {
    optimum = (compare(values[i], *optimum)) ? &values[i] : optimum;
  }
  return optimum;
}

// comparison functions ...
namespace {
  auto less(int,int) -> bool;
  auto greater(int,int) -> bool;
}

auto main() -> int {
  std::vector<int> numbers {91, 18, 92, 22, 13, 43};
  std::cout << "Maximum element: " << *find_optimum(numbers, less)    << '\n';

  // the 2nd parameter to find_optimum instantiates a function greater<int> and
  // then evaluates to a function pointer to that instantiated function!!!
  std::cout << "Minimum element: " << *find_optimum(numbers, greater) << '\n';
}

namespace {
auto less(int left, int right)    -> bool { return left < right; }
auto greater(int left, int right) -> bool { return left > right; }
}
