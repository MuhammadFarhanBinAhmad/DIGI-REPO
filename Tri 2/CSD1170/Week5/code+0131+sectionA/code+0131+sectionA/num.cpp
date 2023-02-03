#include "num.hpp"
#include <iostream>


//NEED TO BE EXPLICIT TO AVOID POTENTIAL ERROR
Num::Num() {
  (*this).val = -999;
}
Num::Num(int i ,double d1,double d2)
{

}

Num::Num(int val) {
  this->val = val;
}

#if 0
Num::Num(Num const& rhs) {
  val = rhs.val;
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

Num& Num::operator=(Num const& rhs) {
  val = rhs.val;
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return *this;
}
#endif

Num& Num::operator=(int rhs) {
  val = rhs;
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return *this;
}

Num& Num::operator+=(Num const& rhs) {
  val += rhs.val;
  return *this;
}

#if 0
Num Num::operator+(Num const& rhs) {
  return Num{val+rhs.val};
}
#else
Num operator+(Num const& lhs, Num const& rhs) {
  Num sum{lhs};
  sum += rhs;
  return sum;
}

Num operator+(Num const& lhs, int rhs) {
  Num sum{lhs};
  sum += static_cast<Num>();
  return sum; 
}

Num operator+(int lhs, Num const& rhs) {
    Num sum{lhs};
  sum += rhs;
  return sum;
}

#endif



void Num::set_val(int v) { val = v; }
int Num::get_val() const { return val; }

std::ostream& operator<<(std::ostream& os, Num const& rhs) {
  os << rhs.get_val();
  return os;
}
