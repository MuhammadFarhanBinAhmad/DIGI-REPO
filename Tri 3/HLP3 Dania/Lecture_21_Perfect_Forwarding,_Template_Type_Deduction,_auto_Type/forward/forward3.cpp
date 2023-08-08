// CSD2125 11/23
// forward3.cpp
// compile/link: g++ -std=c++17 forward3.cpp str.cpp
// Extend the idea from forward2.cpp to implement three factory functions
// that return unique_ptr<Person>

#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include "str.h"
#include "person.h"

std::unique_ptr<Person> factory(Str& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return std::make_unique<Person>(rhs);
}

std::unique_ptr<Person> factory(Str const& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return std::make_unique<Person>(rhs);
}

std::unique_ptr<Person> factory(Str&& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return std::make_unique<Person>(std::move(rhs));
}

int main() {
  Str lv{"lv"};
  Str const rv{"rv"};

  std::cout << "-----------------------\n";

  std::vector<std::unique_ptr<Person>> vx;
  vx.emplace_back(factory(lv));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory(rv));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory(Str()));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory(std::move(lv)));
  std::cout << "-----------------------\n";

  for(auto const& x : vx) {
    std::cout << x->Name() << "\n";
  }
}
