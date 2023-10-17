// CSD2125/CS225 10/23
// forward1.cpp
// compile/link: g++ -std=c++17 forward1.cpp str.cpp
// Perfect forwarding (part 1):
// Suppose you want to write generic code that forwards the
// basic property of passed arguments:
// 1) Modifyable objects should be forwarded so that they can still be modified
// 2) Constant objects should be forwarded as read-only objects
// 3) Movable objects (that can stolen from because they're about to die)
// should be forwarded as movable objects
// This can be achieved without templates by programming all three cases.

#include <utility>
#include <iostream>
#include "str.h"
#include "person.h"

void g(Person&) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

void g(Person const&) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

void g(Person&&) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

// let f() forward its argument val to g()
// val is non-const lvalue => calls g(Person&)
void f(Person& val) {
  g(val);
}

// let f() forward its argument val to g()
// val is const lvalue => calls g(Person const&)
void f(Person const& val) {
  g(val);
}

// let f() forward its argument val to g()
// val is non-const lvalue => needs std::move() to call Person(&&)
void f(Person&& val) {
  g(std::move(val));
}

int main() {
  Person lv{Str{"lv"}};
  Person const rv{Str{"rv"}};

  std::cout << "-----------------------\n";

  f(lv); // f() for nonconstant object calls f(Person&) => calls g(Person&)
  std::cout << "-----------------------\n";
  f(rv); // f() for constant object calls f(Person const&) => calls g(Person const&)
  std::cout << "-----------------------\n";
  f(Person()); // f() for temporary calls f(Person&&) => calls g(Person&&)
  std::cout << "-----------------------\n";
  f(std::move(lv)); // f() for movable variable calls f(Person&&) => calls g(Person&&)
  std::cout << "-----------------------\n";
}
