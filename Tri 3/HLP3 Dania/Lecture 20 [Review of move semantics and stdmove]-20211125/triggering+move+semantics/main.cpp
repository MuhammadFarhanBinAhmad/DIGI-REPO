// CSD2125 11/08
// Code to illustrate that even if a parameter has rvalue reference type,
// since the parameter has a name, the compiler will judge the parameter
// to be an lvalue. To trigger move semantics, you must use std::move.
// Notice that class B's move ctor will not be triggered unless the
// derived class D's move ctor uses std::move.
// Compile: g++ -std=c++17 -D=STR_MOVE -D=STR_DEBUG str.cpp main.cpp
#include <iostream>
#include "str.h"

void foo(Str&& x) {
  Str morex = x;
  std::cout << "x: " << x << " | morex: " << morex << "\n";
}

Str&& goo(Str&& a) {
  return std::move(a);
}

class B {
public:
  B() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  B(const B&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  B(B&&) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  virtual ~B() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

class D : public B {
public:
  D() : B() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  D(const D& rhs) : B(rhs) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  D(D&& rhs) : B(std::move(rhs)) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  virtual ~D() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

D&& funcD(D&& d) {
  return std::move(d);
}

int main() {
  foo("hello");
  std::cout << "------------------------\n";
  Str s = goo(Str("A"));
  std::cout << "s: " << s << "\n";
  std::cout << "------------------------\n";

  D d = funcD(D{});
}