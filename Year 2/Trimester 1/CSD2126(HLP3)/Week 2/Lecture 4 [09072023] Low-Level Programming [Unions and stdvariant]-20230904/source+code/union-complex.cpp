// CSD2125/CS225: 09/14/2020
// union-complex.cpp:
// illustration of maintenance problems with unions containing complex data members:
// 1) You don’t have a way to know what’s the currently used type and
// 2) They won’t call destructors of the underlying types.
// compile & link: g++ -std=c++17 str.cpp union-complex.cpp -D=_DEBUG

#include <iostream>
#include <vector>
#include <string>
#include "str.h"

union U {
  Str s;
  Str s2;
  float f;
  ~U() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

void foo() {
  // calling Str::Str(char const*)
  U u{"hello"};

  // we just constructed u.s, we can do stuff with u.s but we
  // should not touch u.s2 because it is not constructed yet ...
  std::cout << "u.s: " << u.s << "\n";

  // to avoid memory leak, let's destruct u.s before constructing u.s2
  u.s.~Str();

  // let's construct u.s2 so that we can use it rather than u.s
  new (&u.s2) Str("world");
  std::cout << "u.s2: " << u.s2 << "\n";

  // destruct u.s2 because U::~U() is going to be called which won't know to
  // call dtor for u.s2
  u.s2.~Str();
}

union UU {
  UU() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  std::string s;
  std::vector<int> v;
  ~UU() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

template <typename Cont>
void print(Cont const& c, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (const auto& x : c) {
    std::cout << x << " ";
  }
  std::cout << postfix;
}

void boo() {
  UU u; // UU.UU()

  // now call placement new for UU.s
  new (&u.s) std::basic_string<char>("hello");
  std::cout << "u.s: " << u.s << "\n";

  // call dtor for UU.s
  u.s.~basic_string<char>();

  // now call placement new for UU.v
  new (&u.v) std::vector<int>{1,2,3,4};

  // print values in v ...
  print(u.v, "u.v: ");

  // now call dtor for UU.v to avoid memory leak ...
  u.v.~vector<int>();
}

int main() {
  foo();
  std::cout << "-----------------------------------------\n";
  boo();
}
