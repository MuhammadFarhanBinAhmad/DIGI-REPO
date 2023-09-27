// HLP3: 09/23/2023
// optional-int.cpp: The following program demonstrates some abilities 
// of std::optional<> with optional integer types.

#include <iostream>
#include <optional>

// read_int is a function that usually returns a value of type int can
// possibly fail to do so. If reading an integer succeeds, read_int returns
// an std::optional<int> object constructed with the input integer value.
// Otherwise, read_int returns a default constructed std::optional<int> value
// that signals failure or emptiness.
std::optional<int> read_int() {
  int i;
  if (std::cin >> i) { return i; }
  return {};
}

// We can calculate the sum of two optional integers:
std::optional<int> operator+(std::optional<int> lhs, std::optional<int> rhs) {
  return (!lhs || !rhs) ? std::optional<int>{} : std::optional<int>{*lhs + *rhs};
}

// likewise, we can calculate the sum of an optional integer and a plain integer:
std::optional<int> operator+(std::optional<int> lhs, int rhs) {
  return (!lhs) ? std::optional<int>{} : std::optional<int>{*lhs + rhs};
}

int main() {
  std::cout << "Enter two integer values: ";
  std::optional<int> one{read_int()};
  std::optional<int> two{read_int()};

  std::optional<int> sum{one + two + 3};
  if (sum) {
    std::cout << *one << " + " << *two << " + 3: " << *sum << '\n';
  } else {
    std::cout << "Incorrect input!!!\n";
  }
}
