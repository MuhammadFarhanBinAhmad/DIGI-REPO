// CSD2125 11/16
// First example of a simple print function that takes a varying
// number of parameters.
#include <iostream>
#include <string>

// base function reached when parameter pack is empty ...
void print() {
  // empty by design
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

// The varying number of parameters is called a parameter pack.
// 2 kinds of parameter packs:
// template parameter pack represents zero or more template parameters
template <typename T, typename... Types>
// function parameter pack represents zero or more function parameters
void print(T first_param, Types... params) {
  std::cout << first_param << "\n"; // print first parameter
  print(params...); // call print() for remaining arguments 
}

template <typename ... Types>
void print_doubled(Types const& ... params) { // fold expression
  print(params + params...);
}

// another version of print: base case is when parameter pack has
// single value ...
template <typename T>
std::ostream& oprint(std::ostream& os, T const& t) {
  return os << t; // no need for separator after last element in the pack
}

// variadic function template ...
template <typename T, typename... Types>
std::ostream& oprint(std::ostream& os, T const& t, Types const&... params) {
  os << t << ", ";
  return oprint(os, params...);
}

int main() {
  std::string s{"world"};
  //print(7.5, "hello", s);
  print_doubled(7.5, std::string{"hello"}, s);
  //print(7.5+7.5, "hello""hello", s+s)
  std::cout << "------------------------------------------\n";
  oprint(std::cout, 10, s, 42); std::cout << "\n";
}