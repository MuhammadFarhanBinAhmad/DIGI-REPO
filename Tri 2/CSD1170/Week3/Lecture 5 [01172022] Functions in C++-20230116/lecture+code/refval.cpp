// HLP2: refval.cpp
// 01/18/2022
// The following code contains the driver that exercises overloaded functions
// foo [declared in refval.hpp and defined in refval.cpp] and is meant to illustrate
// the idea that function overloading with value and reference types yields will
// almost always fail.

#include <iostream>
#include "refval.hpp"

namespace misc_stuff {

// the declaration of this function [line 27 in refval.hpp] is commented out
// to avoid compiler error messages when overload resolution fails ...
void foo(int x) { 
  std::cout << __PRETTY_FUNCTION__ << ": " << x << "\n";
}

void foo(int& rx) {
  std::cout << __PRETTY_FUNCTION__ << ": " << rx << "\n";
}

void foo(int const& rcx) {
  std::cout << __PRETTY_FUNCTION__ << ": " << rcx << "\n";
}

} // end namespace misc_stuff