// CSD2125 11/23
// forward2.cpp
// compile/link: g++ -std=c++17 forward2.cpp str.cpp
// Extend the idea from forward1.cpp to implement three factory functions:
// for lvalues, for const-lvalues, and for rvalues

#include <utility>
#include <iostream>
#include <vector>
#include "str.h"
#include "person.h"

Person* factory(Str& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return new Person(rhs);
}

Person* factory(Str const& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return new Person(rhs);
}

Person* factory(Str&& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return new Person(std::move(rhs));
}

int main() {
  Str lv{"lv"};
  Str const rv{"rv"};

  std::cout << "-----------------------\n";

  std::vector<Person*> vx;
  vx.emplace_back(factory(lv));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory(rv));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory(Str("move")));
  std::cout << "-----------------------\n";
  vx.emplace_back(factory(std::move(lv)));
  std::cout << "-----------------------\n";
}
