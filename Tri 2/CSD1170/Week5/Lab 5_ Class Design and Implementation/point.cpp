// Since your clients will not have access to this file, your initial
// inclination will be to avoid documenting this file ...
// However, since you're a client too and will need to understand this
// file's contents at a later point in time, the documentation you provide
// now will make the process of maininting this code base easier and more
// efficient.
// Therefore, make sure to provide file-level documentation and some
// function-level documentation for each function that you'll implement to
// avoid unnecessary grade deductions.

#include "point.hpp"  // Point interface
#include <cmath>      // sin, cos, sqrt

///////////////////////////////////////////////////////////////////////////////
// declare private stuff here [if any] in this anonymous namespace ...
namespace {
}

///////////////////////////////////////////////////////////////////////////////

namespace hlp2 {

    Point::Point()
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
	
	//int is default for overload operator

	Point& Point::operator+=(const Point& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;

        return *this;

    } 
	Point& Point::operator+=(const double value)
    {
        this->x += value;
        this->y += value;
        return *this;
    }

	Point& Point::operator++()
    {
        this->x++;
        this->y++;

        return *this;
    }
	Point Point::operator++(int)
    {
        Point old = *this;
        old.x++;
        old.y++;
        return old;
    }

	Point& Point::operator--()
    {
        this->x--;
        this->y--;

        return *this;
    }
	Point Point::operator--(int)
    {
        Point old = *this;
        old.x--;
        old.y--;
        return old;
    }


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
Point operator%(Point,double)
{

}
double operator/( Point& pt1, Point& pt2 )
{

    double distance_x = (pt2[0] - pt1[0]); 
    double distance_y = (pt2[1] - pt1[1]);
    return sqrt((distance_x*distance_x) + (distance_y*distance_y));

}
Point operator+(Point,Point)
{

}
Point operator+(Point,int)
{

}
Point operator+(int,Point)
{

}
Point operator-(Point,Point)
{

}
Point operator-(Point,int)
{

}
Point operator-(int,Point)
{

}
Point operator-(Point)
{

}
Point operator^(const Point,const Point)
{

}
double operator*(const Point,const Point)
{

}
Point operator*(const Point,const double)
{

}
Point operator*(double,const Point)
{

}
std::ostream& operator<<(std::ostream&,const Point&)
{

}
std::istream& operator>>(std::istream&,const Point&)
{

}
} // end hlp2 namespace

///////////////////////////////////////////////////////////////////////////////
// define private stuff here [if any] in this anonymous namespace ...
namespace {
}
