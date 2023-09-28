// CS2125 11/30
// vhierarchy.cpp
// -- allocating/deallocating dudes from the virtual dudes hierarchy

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include "vdude.hpp"

int main() {
  srand(unsigned(time(0)));

  std::vector<std::unique_ptr<Dude>> dudes;
  dudes.emplace_back(std::make_unique<Dude>("D"));
  dudes.emplace_back(std::make_unique<SubDude>("S"));
  dudes.emplace_back(std::make_unique<BadDude>("B"));
  dudes.emplace_back(std::make_unique<MajorDude>("M"));
  dudes.emplace_back(std::make_unique<GodDude>("G"));
  dudes.emplace_back(std::make_unique<OddDude>("O"));

  for (std::unique_ptr<Dude> const& d : dudes) {
    std::cout << d->name() << " punch ";
    if (d->punch()) {
      std::cout << "hits\n";
    } else {
      std::cout << "misses\n";
    }
  }
  std::cout << "\n";

  for (std::unique_ptr<Dude>& pd : dudes) {
    SubDude *sd = dynamic_cast<SubDude*>(pd.get());
    if (sd) {
      std::cout << sd->name() << " squonk ";
      if (sd->squonk()) {
        std::cout << "succeeds\n";
      } else {
        std::cout << "fails\n";
      }
    }
    else {
      std::cout << pd->name() << " cannot sqonk\n";
    }
  }
}
