// HLP2: ref-driver.cpp
// 01/18/2022
// The following code contains the driver that exercises overloaded functions
// foo [declared in refval.hpp and defined in refval.cpp] and is meant to illustrate
// the idea that function overloading with value and reference types yields will
// almost always fail.

#include <iostream>
#include "refval.hpp"

int main() {
  int i {10};
  int& ri{i};
  int const& rci{i};

  misc_stuff::foo(10);   // matches foo(int const&)
  misc_stuff::foo(i);    // matches foo(int&)
  misc_stuff::foo(ri);   // matches foo(int&)
  misc_stuff::foo(rci);  // matches foo(int const&)
}
