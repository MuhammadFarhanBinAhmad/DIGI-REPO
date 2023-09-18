// CSD2125/CS225 05/22/2018
// Provides test cases to study behavior of URVO, NRVO, copy-elision for
// pass-by-value, and limitations of GCC and MSVC to invocation of RVO.
// Class Rig will be used and therefore rig.cpp must be compiled/linked
// to create executable:
// g++ -std=c++17 -O4 elision.cpp rig.cpp
// cl /EHsc /O2 elision.cpp rig.cpp
// In certain cases, NRVO can be hampered in GCC using a specific flag:
// g++ -std=c++17 -fno-elide-constructors elision.cpp rig.cpp

#include <iostream>
#include "rig.h"

Rig urvo() {
  return Rig();
}

Rig nrvo() {
  Rig x;
  x.Mi(11);
  return x;
}

Rig nrvo_ifelse_noelide(int32_t x) {
  Rig a{x}, b{x/2};
  if (x%2) {
    return a;
  } else {
    return b;
  }
}

Rig nrvo_ifelse_noelide2(int x) {
  Rig r;
  if (x%2 == 0) {
    r = Rig(x);
  } else {
    r = Rig(x);
  }
  return r;
}

Rig nrvo_ifelse_elide(int32_t x) {
  Rig a;
  if (x%2) {
    a.Mi(x);
    return a;
  } else {
    a.Mi(x/2);
    return a;
  }
}

Rig urvo_ifelse_elide(int32_t x) {
  if (x%2) {
    return Rig{x};
  } else {
    return Rig{x/2};
  }
}

// copy elision for pass-by-value
void foo(Rig s) {
  std::cout << __PRETTY_FUNCTION__ << "        | s.Mi: " << s.Mi() << '\n';
}

int main() {
  std::cout << "------------------ start: testing urvo() -------------------\n";
  {
    Rig t = urvo();
    std::cout << __PRETTY_FUNCTION__ << "           | ctr: " << Rig::ctr << '\n';
  }
  std::cout << "------------------ end: testing urvo()   -------------------\n";

  std::cout << "------------------ start: testing nrvo() -------------------\n";
  {
    Rig t = nrvo();
    std::cout << __PRETTY_FUNCTION__ << "           | ctr: " << Rig::ctr << '\n';
  }
  std::cout << "------------------ end: testing nrvo()   -------------------\n";

  std::cout << "----------- start: testing nrvo_ifelse_noelide()   -------------\n";
  {
    Rig t = nrvo_ifelse_noelide(11);
    std::cout << __PRETTY_FUNCTION__ << "           | ctr: " << Rig::ctr << '\n';
  }
  std::cout << "----------- end: testing nrvo_ifelse_noelide()   -------------\n";

  std::cout << "----------- start: testing nrvo_ifelse_noelide2()   -------------\n";
  {
    Rig t = nrvo_ifelse_noelide2(11);
    std::cout << __PRETTY_FUNCTION__ << "           | ctr: " << Rig::ctr << '\n';
  }
  std::cout << "----------- end: testing nrvo_ifelse_noelide2()   -------------\n";

  std::cout << "----------- start: testing nrvo_ifelse_elide()   -------------\n";
  {
    Rig t = nrvo_ifelse_elide(11);
    std::cout << __PRETTY_FUNCTION__ << "           | ctr: " << Rig::ctr << '\n';
  }
  std::cout << "----------- end: testing nrvo_ifelse_elide()   -------------\n";

  std::cout << "----------- start: testing urvo_ifelse_elide()   -------------\n";
  {
    Rig t = urvo_ifelse_elide(11);
    std::cout << __PRETTY_FUNCTION__ << "           | ctr: " << Rig::ctr << '\n';
  }
  std::cout << "----------- end: testing urvo_ifelse_elide()   -------------\n";

  std::cout << "----------- start: testing copy-elision for pass-by-value   -------------\n";
  {
    foo(Rig());
  }
  std::cout << "----------- end: testing copy-elision for pass-by-value   -------------\n";
}
