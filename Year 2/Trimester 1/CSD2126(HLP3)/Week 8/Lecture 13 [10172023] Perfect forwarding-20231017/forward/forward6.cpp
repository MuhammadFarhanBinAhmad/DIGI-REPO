// CSD2125/CS225 10/23
// forward6.cpp
// compile/link: g++ -std=c++17 forward6.cpp str.cpp
// Extend the idea from forward5.cpp to implement a perfect forwarding
// factory function that can be used to construct on the heap any
// object T with any kind of constructor (number of parameters and the
// types of these parameters).
// The following code doesn't exercise the variadic parameters - it is
// left as an exercise for the reader. For example, ctros for Person
// can be written to take both Str and int parameters.
#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include "str.h"
#include "person.h"

template <typename T, typename... Params>
std::unique_ptr<T> factory(Params&& ... params) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return std::make_unique<T>(std::forward<Params>(params) ...);
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
