// CSD2125 11/30
// mixin-3.cpp - shows that we can mixin to an arbitrary depth ...
// the only thing missing is the ability to store heterogeneous objects
// in a single container
#include <iostream>
#include <vector>
#include <memory>

// not used ...
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
class Compliment: public T {
public:
  std::string comment() {
    return "Lisa Simpson is smart. " + T::comment();
  }
};
 
template <typename T>
class Insult: public T {
public:
  std::string comment() {
    return "Homer Simpson sucks too!!!";
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
  Dog<Compliment<PositiveVibe>> iCat;
  Cat<Insult    <NegativeVibe>> iDog;
 
  iDog.vocalize();
  iCat.vocalize();

  std::cout << "sizeof(iDog): " << sizeof(iDog) << "\n";
}
