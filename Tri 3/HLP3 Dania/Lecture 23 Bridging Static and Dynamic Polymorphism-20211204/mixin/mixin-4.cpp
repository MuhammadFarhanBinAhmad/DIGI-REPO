// CSD2125 11/30
// mixin-4.cpp - here we add mixins and abstract base class Animal
// to create inheritance hierarchy that can be stored in polymorphic containers
// using pointer to base class Animal...
#include <iostream>
#include <vector>
#include <memory>
 
class Animal {
public:
  virtual void vocalize() = 0;
  virtual ~Animal() = default;
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
class Dog: public T, public Animal {
public:
  void vocalize() { std::cout << "Woof. " << T::comment() << "\n"; }
};
 
template <typename T>
class Cat: public T, public Animal {
public:
  void vocalize() { std::cout << "Meow. " << T::comment() << "\n"; }
};

/*
All of these are valid:
animals.emplace_back(new Cat<NegativeVibe>());
animals.emplace_back(new Dog<NegativeVibe>());
animals.emplace_back(new Cat<PositiveVibe>());
animals.emplace_back(new Dog<PositiveVibe>());
animals.emplace_back(new Cat<Insult<NegativeVibe>>());
animals.emplace_back(new Dog<Insult<NegativeVibe>>());
animals.emplace_back(new Cat<Insult<PositiveVibe>>());
animals.emplace_back(new Dog<Insult<PositiveVibe>>());
animals.emplace_back(new Cat<Compliment<NegativeVibe>>());
animals.emplace_back(new Dog<Compliment<NegativeVibe>>());
animals.emplace_back(new Cat<Compliment<PositiveVibe>>());
animals.emplace_back(new Dog<Compliment<PositiveVibe>>());
*/
int main() {
  std::vector<std::unique_ptr<Animal>> animals;
 
  animals.emplace_back(new Dog<Insult    <PositiveVibe>>());
  animals.emplace_back(new Cat<Compliment<NegativeVibe>>());
  for (auto const& animal: animals) {
    animal->vocalize();
    std::cout << "sizeof(animal): " << sizeof(animal) << "\n";
  }
}
