// CSD2125: helper class to store 2D position coordinates
#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>

template <typename T>
struct Coord {
	Coord(T mx=T{}, T my=T{}) : x(mx), y(my) {}
	T abs() const { return std::sqrt(x*x+y*y); }
	
	T x, y;
};

template <typename T>
Coord<T> operator-(Coord<T> const& lhs, Coord<T> const& rhs) {
	return Coord<T>(lhs.x-rhs.x, lhs.y-rhs.y); 
}

template <typename T>
Coord<T> operator+(Coord<T> const& lhs, Coord<T> const& rhs) {
	return Coord<T>(lhs.x+rhs.x, lhs.y+rhs.y); 
}

template <typename T>
Coord<T> operator*(Coord<T> const& lhs, T rhs) {
	return Coord<T>(lhs.x*rhs, lhs.y*rhs);
}

template <typename T>
Coord<T> operator/(Coord<T> const& lhs, double rhs) {
	return Coord<T>(lhs.x*rhs, lhs.y*rhs);
}

#endif
