// CSD2125 11/30
// static-geom.hpp
// Templates can also be used to implement polymorphism. However, they
// don't rely on the factoring of common behavior as virtual functions
// declared in base classes. Instead, the commonality is implicit in
// that the different "geometric shapes" of an application must support
// operations using a common syntax (that is, having the same name).
// Concrete classes are defined independently of each other. Polymorphic
// behavior is then enabled when templates are instantiated with
// concrete classes.
#ifndef STATIC_GEOM_HPP
#define STATIC_GEOM_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include "coord.hpp"

#if defined(__GNUC__) || defined(__GNUG__)
#define PRINT_PRETTY(os, str) (os << str << __PRETTY_FUNCTION__ << std::endl)
#elif defined(_MSC_VER)
#define PRINT_PRETTY(os, str) (os << str << __FUNCSIG__ << std::endl)
#else
#define PRINT_PRETTY(os, str) (os << str << std::endl)
#endif

// concrete geometric object class Triangle
class Triangle {
public:
	void draw() const { PRINT_PRETTY(std::cout, ""); }
	Coord<double> center_of_gravity() const {
		PRINT_PRETTY(std::cout, "");
		return Coord<double>(vtx[0]+vtx[1]+vtx[2])/3.0;
	}

private:
	Coord<double> vtx[3];
};

// concrete geometric object class Circle
class Circle {
public:
	void draw() const { PRINT_PRETTY(std::cout, ""); }
	Coord<double> center_of_gravity() const { 
		PRINT_PRETTY(std::cout, "");
		return center;
	}

private:
	Coord<double> center;
	double radius;
};

#if 0
// process distance of center of gravity between 
template <typename GeomObj1, typename GeomObj2>
double distance(GeomObj1 const& lhs, GeomObj2 const& rhs) {
	Coord<double> c(lhs.center_of_gravity() - rhs.center_of_gravity());
	return c.abs();  
}
#endif

// process distance of center of gravity between 
template <typename GeomObj1, typename GeomObj2>
double distance(GeomObj1 const *lhs, GeomObj2 const *rhs) {
	Coord<double> c(lhs->center_of_gravity() - rhs->center_of_gravity());
	return c.abs();  
}

// draw any GeomObj
template <typename GeomObj>
void draw(std::unique_ptr<GeomObj> const& pobj) {
	pobj->draw();
}

// draw homogeneous collection of GeomObjs
template <typename GeomObj>
void draw(std::vector<std::unique_ptr<GeomObj>> const& cont) {
	for (auto const& elem : cont) {
		elem->draw();
	}
}

#endif
