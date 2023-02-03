#ifndef NUM_HPP_
#define NUM_HPP_

#include <iostream>

struct Point {
  double x, y;
};

// this is a definition of type Num
class Num {
private:
  int val; // data members

public:
  Num();    // default ctor
  Num(int); // single-argument conversion ctor. Take one only one argument
  Num(int,double =3.14,double = 6.26);
  //explicit Num(int);// explicit function. Need be one for one match. Will not convert for you
  Num(Num const&) = default; // copy ctor

  Num& operator=(Num const& rhs) = default; // copy assignment
  Num& operator=(int rhs);
  // Num i1 {1}, i2{2}, i3{3};
  // i1 = i2

  Num& operator+=(Num const&);
  //Num operator+(Num const& rhs);

  // declarations of the interface of this type
  // mutators
  void set_val(int); // member functions => void set_val(Num *this, int x);
  // accessors
  int get_val() const; // => int get_val(Num const *this);
};

Num operator+(Num const&, Num const&);
Num operator+(Num const&, int);
Num operator+(int, Num const&);
//Num operator+(int, int);

std::ostream& operator<<(std::ostream& os, Num const& rhs);



#endif
