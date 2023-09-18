// CSD2125/CS225 05/22/2018
// Contains definition of member functions of class Rig [defined in rig.h]
// that will be used to study RVO in GCC and MSVC

#include <iostream>
#include "rig.h"

Rig::Rig(int i) : mi{i}             { 
  ++ctr;
  std::cout << __PRETTY_FUNCTION__ << "        | ctr: " << ctr << '\n'; 
}

Rig::Rig(Rig const& rhs) : mi{rhs.mi} {
  ++ctr;
  std::cout << __PRETTY_FUNCTION__ << " | ctr: " << ctr << '\n';
}

Rig::~Rig() {
  --ctr;
  std::cout << __PRETTY_FUNCTION__ << "          | ctr: " << ctr << '\n';
}

Rig& Rig::operator=(Rig const& rhs) { 
  mi = rhs.mi;
  std::cout << __PRETTY_FUNCTION__ << " | ctr: " << ctr << '\n';
  return *this;
}

int32_t Rig::ctr = 0;
