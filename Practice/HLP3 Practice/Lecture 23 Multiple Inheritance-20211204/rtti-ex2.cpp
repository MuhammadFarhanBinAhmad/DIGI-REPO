// CS2125 11/30
// rtti-ex2.cpp
// -- which Dude am I? (type id version)

#include <typeinfo>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
#include "dude.hpp"

std::string attempt(bool x) {
  return (x) ? "succeeds" : "fails";
}

int main() {
  // Dude class hierarchy uses pseudo-random numbers generated by
  // standard library - therefore, make sure to set the generator's seed
  srand(unsigned(time(0)));

  std::array<Dude*, 6> dudes;
  dudes[0] = new Dude("D");
  dudes[1] = new SubDude("S");
  dudes[2] = new BadDude("B");
  dudes[3] = new MajorDude("M");
  dudes[4] = new GodDude("G");
  OddDude *odp = new OddDude("O");
  BadDude *bdp = odp;
  dudes[5] = bdp;

  for (Dude const *d : dudes) {
    std::cout << d->name() << " punch " << attempt(d->punch()) << std::endl;
  }
  std::cout << std::endl;

  // The typeid operator provides a program the ability to use a pointer's (or
  // reference's) dynamic type to retrieve the actual type of the derived-class
  // object referred to by the pointer (or reference). This operator along with 
  // dynamic_cast provide support for run-time type identification (RTTI) in C++. 
  
  int index = rand()%6;
  if (typeid(*dudes[index]) == typeid(SubDude)
      || typeid(*dudes[index]) == typeid(OddDude)) {
    SubDude *sdp = dynamic_cast<SubDude*>(dudes[index]);
    std::cout << sdp->name() << " squonk "
         << attempt(sdp->squonk()) << std::endl;
  } else {
    std::cout << dudes[index]->name() << " cannot squonk ("
         << typeid(*dudes[index]).name() << " type)" << std::endl;   
  }

  if (typeid(*dudes[index]) == typeid(MajorDude)
      || typeid(*dudes[index]) == typeid(GodDude)) {
    MajorDude *mdp = dynamic_cast<MajorDude*>(dudes[index]);
    std::cout << mdp->name() << " stab " << attempt(mdp->stab()) << std::endl; 
  } else {
    std::cout << dudes[index]->name() << " cannot stab ("
         << typeid(*dudes[index]).name() << " type)" << std::endl;
  }
  std::cout << std::endl;
  
  for (Dude *pd : dudes) {
    std::cout << typeid(*pd).name() << std::endl;
    delete pd;
  }
}