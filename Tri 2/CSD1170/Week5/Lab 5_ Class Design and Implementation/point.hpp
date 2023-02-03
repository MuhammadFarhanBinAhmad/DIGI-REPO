// make sure to provide file-level documentation and function-level
// documentation for each function that you'll implement to avoid
// unnecessary grade deductions.

////////////////////////////////////////////////////////////////////////////////
#ifndef POINT_HPP
#define POINT_HPP
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // istream, ostream

namespace hlp2 {
	
class Point {
public:
	// declare constructors (3)
	Point();
	Point (double,double);
	Point (const double*);
	// declare overloaded operators (8 member functions)
	
	//int is default for overload operator

	Point& operator+=(const Point&);//return the result by ref 
	Point& operator+=(const double);//return a double because

	Point& operator++();//use ref because want to directly change value. If not, local will be use and detroy when function ends
	Point operator++(int);//Special c++. C++ will ignoer the int variable in a  ++/-- variable

	Point& operator--();//use ref because want to directly change value. If not, local will be use and detroy when function ends
	Point operator--(int);//Special c++. C++ will ignoer the int variable in a  ++/-- variable


	double& operator[](int);
	double operator[](int) const;
	//if const is on the left,
	//if const is on the right, the function will not change any data in the input

private:
	double x; // The x-coordinate of a Point
	double y; // The y-coordinate of a Point
};
// declare 15 non-member, non-friend functions 


Point operator%(Point,double);
double operator/(const Point&,const Point&);
Point operator+(Point,Point);
Point operator+(Point,int);
Point operator+(int,Point);
Point operator-(Point,Point);
Point operator-(Point,int);
Point operator-(int,Point);
Point operator-(Point);
Point operator^(const Point,const Point);
double operator*(const Point,const Point);
Point operator*(const Point,const double);
Point operator*(double,const Point);
std::ostream& operator<<(std::ostream&,const Point&);
std::istream& operator>>(std::istream&,const Point&);


} // end namespace hlp2

#endif // end POINT_HPP
////////////////////////////////////////////////////////////////////////////////
