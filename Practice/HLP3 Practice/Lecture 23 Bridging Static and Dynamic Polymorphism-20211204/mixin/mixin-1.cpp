// CSD2125 11/30
// mixin-1.cpp
// No mixins yet... This is an example of dynamic polymorphism with the
// ability to store heterogeneous objects of an inheritance hierarchy in
// a container.
#include <iostream>
#include <vector>
#include <memory>
 
class Animal {
public:
  virtual void vocalize() = 0;
};
 
class Dog: public Animal {
public:
  void vocalize() { std::cout << "Woof." << std::endl; }
};
 
class Cat: public Animal {
public:
  void vocalize() { std::cout << "Meow." << std::endl; }
};
 
int main() {
  std::vector<std::unique_ptr<Animal>> animals;
  animals.emplace_back(new Dog());
  animals.emplace_back(new Cat());
 
  for (auto &animal: animals) { 
    animal->vocalize();
  }
}
