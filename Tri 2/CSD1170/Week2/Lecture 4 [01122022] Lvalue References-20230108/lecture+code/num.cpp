// HLP2: num.cpp
// 01/18/2022
// The following code illustrates the definition of member functions
// of type Num and associated global functions

#include "num.hpp"

namespace hlp2 {

// constructors have no return value ...
Num::Num() : i{} { std::cout << __PRETTY_FUNCTION__ << "\n"; }

// single-argument constructor
Num::Num(int val) : i{val} { std::cout << __PRETTY_FUNCTION__ << "\n"; }

// copy constructor
Num::Num(Num const& rhs) : i{rhs.i} { std::cout << __PRETTY_FUNCTION__ << "\n"; }

// define destructor
Num::~Num() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

// copy assignment operator
Num& Num::operator=(Num const& rhs) {
  i = rhs.i;
  return *this;
}

Num& Num::operator=(int rhs) {
  i = rhs;
  return *this;
}  

// overload operator +=
Num& Num::operator+=(Num const& rhs) {
  i += rhs.i;
  return *this;
}

// overload operator +=
Num& Num::operator+=(int rhs) {
  i += rhs;
  return *this;
}

// define global functions ...
// declare global functions to overload operator +
Num operator+(Num const& lhs, Num const& rhs) {
  Num result{lhs};
  result += rhs;
  return result;
}

Num operator+(Num const& lhs, int rhs) {
  Num result{lhs};
  result += rhs;
  return result;
}

Num operator+(int lhs, Num const& rhs) {
  Num result{lhs};
  result += rhs;
  return result;
}

// define global function to overload operator <<
std::ostream& operator<<(std::ostream& os, Num const& rhs) {
  os << rhs.I();
  return os;
}

} // end namespace hlp2
