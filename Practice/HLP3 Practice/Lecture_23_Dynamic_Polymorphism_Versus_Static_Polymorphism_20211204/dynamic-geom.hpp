// CSD2125 11/30
// dynamic-geom.cpp defines a simple example of polymorphic classes
// implemented via inheritance.
#ifndef DYNAMIC_GEOM_HPP
#define DYNAMIC_GEOM_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "coord.hpp"

#if defined(__GNUC__) || defined(__GNUG__)
#define PRINT_PRETTY(os, str) (os << str << __PRETTY_FUNCTION__ << std::endl)
#elif defined(_MSC_VER)
#define PRINT_PRETTY(os, str) (os << str << __FUNCSIG__ << std::endl)
#else
#define PRINT_PRETTY(os, str) (os << str << std::endl)
#endif

// common abstract base class GeomObj for geometric objects
class GeomObj {
public:
  virtual ~GeomObj() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	virtual void draw() const = 0;
	// return center of gravity of geometric object:
	virtual Coord<double> center_of_gravity() const = 0;
private:
// nothing of importance
};

// concrete geometric object class Triangle - derived from GeomObj
class Triangle : public GeomObj {
public:
  virtual ~Triangle() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	virtual void draw() const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	virtual Coord<double> center_of_gravity() const {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return Coord<double>(vtx[0]+vtx[1]+vtx[2])/3.0;
	}
private:
	Coord<double> vtx[3];
};

// concrete geometric object class Circle - derived from GeomObj
class Circle : public GeomObj {
public:
  virtual ~Circle() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	virtual void draw() const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	virtual Coord<double> center_of_gravity() const { 
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return center;
	}
private:
	Coord<double> center;
	double radius;
};

// process distance of center of gravity between GeomObjs
// process distance of center of gravity between GeoObjs
Coord<double> distance(GeomObj const& lhs, GeomObj const& rhs) {
	Coord<double> c(lhs.center_of_gravity() - rhs.center_of_gravity());
	return c.abs(); 
}

// process distance of center of gravity using GeoObj pointers
Coord<double> distance(std::unique_ptr<GeomObj> const& lhs, std::unique_ptr<GeomObj> const& rhs) {
	Coord<double> c(lhs->center_of_gravity() - rhs->center_of_gravity());
	return c.abs(); 
}

// draw non-homogeneous collection of GeoObjs
void draw(std::vector<std::unique_ptr<GeomObj>> const& cont) {
	for (auto const& elem : cont) {
		elem->draw();
	}
}

// draw any GeomObj
void draw(std::unique_ptr<GeomObj> const& rhs) {
	rhs->draw();	// call draw() according to the type of the object
}

#endif
