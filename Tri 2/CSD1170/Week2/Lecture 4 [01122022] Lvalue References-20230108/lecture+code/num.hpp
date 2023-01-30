// HLP2: num.hpp
// 01/18/2022
// The following code illustrates the definition of a type Num using
// data abstraction and encapsulation mechanisms provided by C++

#include <iostream>

#ifndef NUM_HPP_
#define NUM_HPP_

namespace hlp2 {

// User-defined Num encapsulates a plain-old int ...
struct Num {
private:
  int i; // private data
public:
  // default constructor
  Num();
  // single-argument constructor
  Num(int val);
  // copy constructor
  Num(Num const& rhs);
  // define destructor
  ~Num();

  // copy assignment operator
  Num& operator=(Num const& rhs);
  Num& operator=(int rhs);

  // overload operator +=
  Num& operator+=(Num const& rhs); // num1 += num2
  Num& operator+=(int rhs);        // num1 += 2

  // modifier - changes value of private int value ...
  void I(int value);
  // accessor - get value of private int value ...
  int I() const;
};

// inline modifier function to change value of private int value ...
inline void Num::I(int value) {
  i += value;
}

// inline accessor function to return value of private int value ...
inline int Num::I() const {
  return i;
}

// declare global functions to overload operator +
Num operator+(Num const& lhs, Num const& rhs); // num3 = num1 + num2
Num operator+(Num const& lhs, int rhs); // num3 = num1 + 2
Num operator+(int lhs, Num const& rhs); // num3 = 3 + num1

// declare global function to overload operator <<
std::ostream& operator<<(std::ostream& os, Num const& rhs); // std::cout << num1

} // end namespace hlp2

#endif // #ifndef NUM_HPP_
