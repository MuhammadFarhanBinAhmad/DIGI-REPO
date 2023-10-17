// CSD2125/CS225 10/23
// forward4.cpp
// compile/link: g++ -std=c++17 forward4.cpp str.cpp
// Extend the idea from forward3.cpp to implement a single generic factory function
// that returns unique_ptr<Person>.
// Notice that the function parameter type is Param&& to incorporate
// forwarding references that use generic code to replace the three separate
// non-generic functions.
// However, you will see that move semantics are not enabled when they should be
// (for calls to the factory with rvalue references).

#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include "str.h"
#include "person.h"

template <typename T, typename Param>
std::unique_ptr<T> factory(Param&& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return std::make_unique<T>(rhs);
}

int main() {
  Str lv{"lvalue"};
  Str const rv{"const-lvalue"};

  std::cout << "-----------------------\n";

  std::vector<std::unique_ptr<Person>> vx;
  vx.emplace_back(factory<Person>(lv));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory<Person>(rv));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory<Person>(Str("rvalue")));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory<Person>(std::move(lv)));
  std::cout << "-----------------------\n";

  for(auto const& x : vx) {
    std::cout << x->Name() << "\n";
  }
  std::cout << "-----------------------\n";
}
