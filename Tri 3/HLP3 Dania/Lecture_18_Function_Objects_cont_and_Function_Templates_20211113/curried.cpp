// CSD2125: 11/11
// Example of currying [Haskell Curry]
// Idea behind currying: Suppose you're working in a programming
// language that doesn't let you create functions that have more
// than a single argument.
// That is, instead of creating a function that takes two arguments
// and returns a single value, you create a unary function that
// returns a second unary function.
// When this second unary function is called, this means you've
// received both needed arguments and can then return the
// resulting value.

#include <iostream>

bool greater(double first, double second) {
  return first > second;
}

auto greater_curried(double first) {
  return [first](double second) {
    return first > second;
  };
}

int main() {
  // binary function returns true/false
  std::cout << std::boolalpha << greater(2, 3) << "\n";
  // unary function that returns a unary function object that
  // will check whether its argument is less than 2
  greater_curried(2);
  // returns false
  std::cout << std::boolalpha << greater_curried(2)(3) << "\n";
}
