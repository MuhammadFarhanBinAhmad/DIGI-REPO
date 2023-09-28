// CSD2125 11/30
// dynamic-main.cpp illustrates the exercise of the polymorphic hierarchy
// defined in dynamic-geom.hpp.
// After creating concrete objects, client code can manipulate these objects
// references or pointers to the base class, which enables the virtual
// function dispatch mechanism. Calling a virtual member function through a
// pointer or reference to a base class results in an invocation of the
// appropriate member function of the specific concrete object to which
// the reference or pointer points to.
// The use of virtual pointers and virtual tables to implement virtual
// function dispatch mechanism is illustrated in pptx slides.
// Dynamic polymorphism exhibits the following strengths in C++:
// 1) Heterogeneous collections are handled elegantly.
// 2) The executable code size is potentially smaller (because only one
// polymorphic function is needed whereas distinct template instance
// must be generated to handle different types.)
// 3) Code can be entirely compiled, hence no implementation source must
// be published (distributing template libraries usually requires distribution
// of the source code of the template implementations).
// Compile: g++ -std=c++17 dynamic-main.cpp
#include "coord.hpp"
#include "dynamic-geom.hpp"

int main() {
	// heterogeneous collection ...
	std::vector<std::unique_ptr<GeomObj>> coll;
	coll.emplace_back(std::make_unique<Triangle>());
	coll.emplace_back(std::make_unique<Circle>());
	
  // draw all objects of base class type GeomObj in container
	draw(coll);
  // find distance between two previously defined GeomO
	distance(coll[0], coll[1]);
  // draw one object
  draw(coll[0]);
}
