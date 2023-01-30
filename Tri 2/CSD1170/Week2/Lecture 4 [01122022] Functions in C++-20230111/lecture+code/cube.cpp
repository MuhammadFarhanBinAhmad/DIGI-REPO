#include <iostream>
#include "cube.hpp"

namespace misc_stuff {

int cube(int x) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return x*x*x;
}

long cube(long x) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return x*x*x;
}

float cube(float x) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return x*x*x;
}

double cube(double x) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return x*x*x;
}

} // end namespace misc_stuff
