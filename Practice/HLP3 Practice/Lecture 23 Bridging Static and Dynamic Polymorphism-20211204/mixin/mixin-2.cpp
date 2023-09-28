// CSD2125 11/30
// mixin-2.cpp - shows static polymorphism with template mixins
// That is, we're mixing in classes NegativeVibe and PositiveVibe to the 
// Dog and Cat class templates.
// Mixins provide an alternative way to customize the behavior of a
// type without inheriting from it.
// Think about this ... If your derived class Dog needs to sometimes
// have NegativeVibes and sometimes PositiveVibes (but never both
// together), then multiple inheritance is one possible option:
// inherit the Dog class from both NegativeVibe and PositiveVibe base classes.
// Mixins avoid multiple inheritance by essentially inverting the
// normal direction of inheritance, because the new vibe classes are "mixed in"
// to the inheritance hierarchy as base classes of a class template rather
// than being created as a new derived class. This approach allows the
// introduction of new data members and other operations without requiring
// any duplication of the interface.
#include <iostream>
#include <vector>
#include <memory>

// not used in this example ...
class Animal {
public:
  virtual void vocalize() = 0;
};
 
class NegativeVibe {
public:
  std::string comment() {
    return "Bart Simpson sucks!!! ";
  }
};
 
class PositiveVibe {
public:
  std::string comment() {
    return "I like Lisa Simpson! ";
  }
};
 
template <typename T>
class Dog: public T {
public:
  void vocalize() { std::cout << "Woof. " << T::comment() << "\n"; }
};
 
template <typename T>
class Cat: public T {
public:
  void vocalize() { std::cout << "Meow. " << T::comment() << "\n"; }
};
 
int main() {
  // we can have Cats and Dogs with PositiveVibe or NegativeVibe -
  // all without multiple inheritance ...
  Cat<PositiveVibe> iCat;
  Dog<NegativeVibe> iDog;
  Cat<NegativeVibe> nCat;
  Dog<PositiveVibe> pDog;
 
  iDog.vocalize();
  iCat.vocalize();
  pDog.vocalize();
  nCat.vocalize();
}