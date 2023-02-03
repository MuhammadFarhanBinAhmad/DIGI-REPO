#ifndef NUM_HPP_
#define NUM_HPP_

#include <iostream>

class Num {
private:
  int val {-999}; // data member with in-class member initializer

public:
  Num(); // default constructor
  Num(int); // single-argument ctor
  Num(Num const&) = default; // copy ctor

  Num& operator=(Num const&) = default; // copy assignment
  Num& operator=(int);
  // Num i1{1}, i2{2}, i3{3};
  // i1 = i2 = 15
  // ++(i1 = i2)

  Num& operator+=(Num const&);
  Num& operator+=(int);

  // accessors
  int get_val() const;
  // mutators
  void set_val(int);
};

Num operator+(Num const& lhs, Num const& rhs);
Num operator+(Num const& lhs, int rhs);
Num operator+(int lhs, Num const& rhs);
//Num operator+(int lhs, int rhs);

std::ostream& operator<<(std::ostream&, Num const& rhs);

#endif
