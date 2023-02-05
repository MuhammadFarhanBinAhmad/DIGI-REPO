// make sure to provide file-level documentation and function-level
// documentation for each function that you'll implement to avoid
// unnecessary grade deductions.
/******************************************************************************/
/*!
\file   point.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Lab 4: Constructors and Operator Overloading
\date   04/02/2022
\brief
  A script does the following:
  3 Constructor-
  
  8 Member Function-
  2 operator[] - Take in index which return the value(think like array but can put any array in it because you only care about accessing it) 
  2 operator+= - Work the same as the in-built type
  2 operator++ - Increment the value. Work same as the in-built type
  2 operator-- - Decrement the value. Work same as the in-built type
  15 Non Member Function-
  % (Rotation) - Rotation of a vector
  / (Distance) - Calculate distance between 2 vector
  +/- (Translation) - Handle translation of a vector
  - (Negation) -  Negation of a vector
  ^ (MidPoint) - Calculate the midpoint value
  * (Dot Product) - Calculate the dot product of 2 points
  * (Scale) - Scaling of a vector
  << (Output) - Print out vector
  >> (Input) - Read from input stream and allocate data


*/
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
	Point& operator+=(double);//return a double because

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

//ROTATION
Point operator%(const Point&,double);
//DISTANCE
double operator/( Point&, Point&);
//TRANSLATION
Point operator+( Point, Point);
Point operator+(Point,int);
Point operator+(int,Point);
Point operator-(Point pt1,Point pt2);
Point operator-(Point,int);
Point operator-(int,Point);
Point operator-(Point);
Point operator^(const Point,const Point);
//DOT PRODUCT
double operator*(const Point,const Point);
//SCALING
Point operator*(const Point,const double);
Point operator*(double,const Point);
//OUTPUT
std::ostream& operator<<(std::ostream&,const Point&);
//INPUT
std::istream& operator>>(std::istream&,Point&);


} // end namespace hlp2

#endif // end POINT_HPP
////////////////////////////////////////////////////////////////////////////////
