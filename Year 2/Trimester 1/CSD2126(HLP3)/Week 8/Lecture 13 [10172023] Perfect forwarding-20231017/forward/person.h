#ifndef PERSON_H
#define PERSON_H

#include "str.h"
#include <iostream>
#include <utility>

class Person {
public:
  Person() : name{""}, age{10} { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  
  Person(Str const& rhs) : name{rhs}, age{10} { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  Person(Str&& rhs) : name{std::move(rhs)}, age{10} { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  
  Person(Person const& rhs) : name{rhs.name}, age{10} { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  Person(Person&& rhs) : name{std::move(rhs.name)}, age{10} { std::cout << __PRETTY_FUNCTION__ << "\n"; }

  Person& operator=(Str const& rhs) { name = rhs; std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
  Person& operator=(Str&& rhs) { name = std::move(rhs); std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }

  Person& operator=(Person const& rhs) { name = rhs.name; age = rhs.age; std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }
  Person& operator=(Person&& rhs) { name = std::move(rhs.name); age = rhs.age; std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; }

  ~Person() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  Str const& Name() const { return name; }
  int Age() const { return age; }
private:
  Str name;
  int age;
};

#endif
