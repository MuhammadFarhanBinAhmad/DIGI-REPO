// HLP2: cube.hpp
// 01/18/2022
// The following code contains the driver that exercises overloaded functions
// cube [declared in cube.hpp and defined in cube.cpp] and is meant to illustrate
// the idea that function overloading with built-in types yields surprising results.
// Therefore, Well-designed systems must not include functions with parameters
// that are closely related or such a system must provide explicit overloads
// for every built-in type [just as the standard library does for operator<< functions
// for std::ostream class or for operator>> functions for std::istream class]

#ifndef CUBE_HPP
#define CUBE_HPP

namespace misc_stuff {

int cube(int);
float cube(float);
double cube(double);
long cube(long);

} // end misc_stuff


#endif

