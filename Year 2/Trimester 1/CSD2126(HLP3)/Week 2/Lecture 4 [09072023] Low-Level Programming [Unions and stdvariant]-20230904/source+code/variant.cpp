// CSD2125/CS225: 05/14/2018
// variant.cpp: illustrates the advantages of std::variant over unions.
// The problems with unions is that you don’t have a way to know what’s
// the currently used type and they won’t call destructors of the
// underlying types.
// std::variant template class is a discriminated union that solves the
// above two disadvantages of unions.

#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

template<typename T>
std::ostream&
std::operator<<(std::ostream& os, std::vector<T> const& rhs) {
  os << "< ";
  for (T const& x : rhs) {
    os << x << " ";
  }
  os << ">";
  return os;
}

int main() {
  std::variant<int, double> v, w;
  v = 123; // activate v<int>
  try {
    int i = std::get<int>(v); // i is 123
    int j = std::get<0>(v);  // j is also 123
    w = std::get<int>(v); // w's int is now activated
    v = 456.789; // v<double> is set
    w = v; // w is equivalent to v
    std::cout << "w<int>: " << std::get<int>(w) << "\n";
  } catch(std::bad_variant_access const& e) {
    std::cout << e.what() << "\n";
  }

  std::variant<std::vector<int>, std::string> vs;
  vs = "hello world";
  std::cout << "which member set: " 
            << vs.index() << "\n";
  std::cout << std::get<std::string>(vs) << "\n";

  vs = std::vector<int>{1,2,3,4};
  std::cout << std::get<std::vector<int>>(vs) << "\n";
}
