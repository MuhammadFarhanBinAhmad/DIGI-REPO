// CSD2125 11/30
// static-main.cpp
// This source file illustrates the exercise of static polymorphism via
// class templates implemented in static-geom.hpp.
// The following can be said about static polymorphism in C++:
// 1) Interface commonality need not be expressed thro' a common base class.
// 2) Generated code is potentially faster because no indirection thro'
// virtual pointer is needed a priori and nonvirtual functions can be
// inlined much more often.
// 3) Concrete types that provide only partial interfaces can still be
// used if only that part ends up being exercised by the application.
// Compile: g++ -std=c++17 static-main.cpp
#include "coord.hpp"
#include "static-geom.hpp"

int main() {
	std::vector<std::unique_ptr<Triangle>> tri_coll;
	tri_coll.emplace_back(std::unique_ptr<Triangle>());
	tri_coll.emplace_back(std::unique_ptr<Triangle>());
	draw(tri_coll);
	
	std::vector<std::unique_ptr<Circle>> circle_coll;
	circle_coll.emplace_back(std::unique_ptr<Circle>());
	circle_coll.emplace_back(std::unique_ptr<Circle>());
	draw(circle_coll);

	double dist = distance(tri_coll[0].get(), circle_coll[0].get());
	std::cout << "dist: " << dist << "\n";

}
