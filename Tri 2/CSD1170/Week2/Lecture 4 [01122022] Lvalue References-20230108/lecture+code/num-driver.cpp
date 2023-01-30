// HLP2: num-driver.cpp
// 01/18/2022
// The following code illustrates the exercise of user-defined type Num.
// Compile and link like this:
// g++ -std=c++17 -pedantic -Wall -Wextra -Werror num-driver.cpp num.cpp -o num.out

#include <iostream>
#include "num.hpp"
#include <cstdlib>

// this is a using directive that brings into scope the name Num from namespace hlp2
using hlp2::Num;

int main() {
  Num n1, n2{2}, n3{3};
  n1 += n2 += n3;
  Num n4 = n2;
  n2 = 1;
  std::cout << "n2: " << n2.I() << "\n";
  n4 = n1 + n2 + n3 + 10;
  std::cout << "n1: " << n1 << " | n2: " << n2 << " | n3: " << n3 << " | n4: " << n4 << "\n";

  // notice that new not only allocates memory for a Num object but it also
  // calls the corresponding constructor.
  Num *pn1 = new Num{10};
  std::cout << "*pn1: " << *pn1 << "\n";
  // likewise, delete operator will first call the destructor before
  // returning the memory back to the free store.
  delete pn1;

  // notice that malloc just allocated memory - it doesn't call the constructor
  // to initialize the object of type Num ...
  Num *pn2 = (Num*) std::malloc(sizeof(Num));
  std::cout << "*pn2: " << *pn2 << "\n"; // printing state of uninitialized object
  // notice that free doesn't call the destructor before returning the
  // memory allocated to the Num object back to the free store.
  std::free(pn2);
}