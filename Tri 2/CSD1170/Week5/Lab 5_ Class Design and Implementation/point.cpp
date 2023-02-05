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
/******************************************************************************/

#include "point.hpp"  // Point interface
#include <cmath>      // sin, cos, sqrt
double const PI {3.14159265358979323846};
///////////////////////////////////////////////////////////////////////////////
// declare private stuff here [if any] in this anonymous namespace ...
namespace {
}

///////////////////////////////////////////////////////////////////////////////

namespace hlp2 {

    Point::Point(): x{0}, y{0}
    {

    }
	Point::Point (double lhs,double rhs)
    {
        x = lhs;
        y = rhs;
    }
	Point::Point (const double* pt)
    {
        x = *pt;

        y = *(++pt);
    }
	// declare overloaded operators (8 member functions)
	
    //TRANSLATION
	Point& Point::operator+=(const Point& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;

    } 
	Point& Point::operator+=(double value)
    {
        this->x += value;
        this->y += value;
        return *this;
    }
    //PREFIX/POSTFIX INCREMENT
	Point& Point::operator++()
    {
        this->x++;
        this->y++;

        return *this;
    }
	Point Point::operator++(int)
    {
        Point old = *this;
        x++;
        y++;
        return old;
    }
    //PREFIX/POSTFIX DECREMENT
	Point& Point::operator--()
    {
        this->x--;
        this->y--;

        return *this;
    }
	Point Point::operator--(int)
    {
        Point old = *this;
        x--;
        y--;
        return old;
    }
    //ACCESSOR
	double& Point::operator[](int index)
    {
        if (index == 0)
        {
            return x;
        }
        else
        {
            return y;
        }
    }
	double Point::operator[](int index) const
    {
        if (index == 0)
        {
            return x;
        }
        else
        {
            return y;
        }
    }
// define 3 constructors
// define 8 member functions
// define 15 non-member, non-friend functions
//ROTATION
Point operator%(const Point& pt,double degree)
{
    return Point{
    pt[0] * cos(degree * PI/180) - pt[1] * sin(degree*PI/180), 
    pt[0] * sin(degree * PI/180) + pt[1] * cos(degree * PI/180)
    };
}
//DISTANCE
double operator/( Point& pt1, Point& pt2 )
{

    double distance_x = (pt2[0] - pt1[0]); 
    double distance_y = (pt2[1] - pt1[1]);
    return sqrt((distance_x*distance_x) + (distance_y*distance_y));

}
//TRANSLATION
Point operator+( Point pt1, Point pt2)
{

    pt1[0] += pt2[0];
    pt1[1] += pt2[1];
    return pt1;
    
}
Point operator+(Point pt1,int value)
{
    Point temp;
    temp[0] = pt1[0]+value;
    temp[1] = pt1[1]+value;
    return temp;
}
Point operator+(int value,Point pt1)
{
    Point temp;
    temp[0] = value+pt1[0];
    temp[1] = value+pt1[1];
    return temp;
}
Point operator-( Point pt1, Point pt2)
{
    Point temp;

    temp[0] = pt1[0] - pt2[0];
    temp[1] = pt1[1] - pt2[1];
    
    return temp;
}
Point operator-(Point pt1,int value)
{
    Point temp;
    temp[0] = pt1[0]-value;
    temp[1] = pt1[1]-value;
    return temp;
}
Point operator-(int value,Point pt1)
{
    Point temp;
    temp[0] = value-pt1[0];
    temp[1] = value-pt1[1];
    return temp;
}
//NEGATION
Point operator-(Point pt)
{
    pt[0] = -pt[0];
    pt[1] = -pt[1];
    return pt;
}
//MIDPOINT
Point operator^(const Point pt1,const Point pt2)
{
    Point temp;
    temp[0] = (pt1[0] + pt2[0]) / 2;
    temp[1] = (pt1[1] + pt2[1]) / 2;
    return temp;
}
//DOT PRODUCT
double operator*(const Point a,const Point b)
{
    return (a[0] * b[0]) +  (a[1] * b[1]);
}
//SCALE
Point operator*(const Point pt,const double scale)
{
    Point temp;
    temp[0] = pt[0] * scale;
    temp[1] = pt[1] * scale;
    return temp;

}
Point operator*(double scale,const Point pt)
{
    Point temp;
    temp[0] = pt[0] * scale;
    temp[1] = pt[1] * scale;
    return temp;
}
//OUTPUT
std::ostream& operator<<(std::ostream& out,const Point& pt)
{
    return out << '(' << pt[0] << ", " << pt[1] << ")";
}
//INPUT
std::istream& operator>>(std::istream& is, Point& pt)
{
    is >>  pt[0] >> pt[1];
    return is;

}
} // end hlp2 namespace

///////////////////////////////////////////////////////////////////////////////
// define private stuff here [if any] in this anonymous namespace ...
namespace {
}
