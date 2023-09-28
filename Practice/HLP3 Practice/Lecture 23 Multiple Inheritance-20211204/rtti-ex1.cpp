// CS2125 11/30
// rtti-ex1.cpp
// -- which Dude am I?  (dynamic_cast version)

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include "dude.hpp"

// Inheritance gives rise to pointers and references with two different types:
// a static type and a dynamic type. The static type of a pointer or reference
// is its declared type. The dynamic type is determined by the type of object
// it actually refers to. Dynamic types can change as a program runs, typically
// through assignments. Virtual functions are dynamically bound, meaning that
// the particular function called is determined by the dynamic type of the object
// through which it's invoked. This run-time polymorphic behavior is illustrated
// in the following source code.

std::string attempt(bool x) {
  return x ? "succeeds" : "fails";
}

int main() {
  srand(unsigned(time(0)));

  std::vector<std::unique_ptr<Dude>> dudes;
  dudes.emplace_back(std::make_unique<Dude>("D"));
  dudes.emplace_back(std::make_unique<SubDude>("S"));
  dudes.emplace_back(std::make_unique<BadDude>("B"));
  dudes.emplace_back(std::make_unique<MajorDude>("M"));
  dudes.emplace_back(std::make_unique<GodDude>("G"));
  std::unique_ptr<OddDude> odp = std::make_unique<OddDude>("O"); // up-cast
  std::unique_ptr<BadDude> bdp; bdp.reset(odp.release());
  dudes.emplace_back(bdp.release());

  for (std::unique_ptr<Dude> const& pd : dudes) {
    std::cout << pd->name() << " punch " << attempt(pd->punch()) << "\n";
  }
  std::cout << "\n";

  int index = rand()%6;
  /*
  The dynamic_cast operator performs type-safe down-casts -  the safe conversion
  of a base-class pointer (or reference) to a derived-class pointer (or reference).
  Down-casting through dynamic_cast requires run-time polymorphic behavior involving
  virtual functions. 
  */
  SubDude *sdp = dynamic_cast<SubDude*>(dudes[index].get()); // down-cast
  if (sdp) {
    std::cout << sdp->name() << " squonk " << attempt(sdp->squonk()) << std::endl;
  } else {
    std::cout << dudes[index]->name() << " cannot squonk" << std::endl;
  }

  MajorDude *mdp = dynamic_cast<MajorDude*>(dudes[index].get()); // down-cast
  if (mdp) {
    std::cout << mdp->name() << " stab " << attempt(mdp->stab()) << std::endl;
  } else {
    std::cout << dudes[index]->name() << " cannot stab" << std::endl;
  }
}
