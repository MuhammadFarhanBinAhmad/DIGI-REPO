// HLP2
// Implementation file: Since the Sphere class interface is implemented as
// inline functions, we only need to define static data members and member
// functions that were previously declared in class Sphere.
// See the handout for more details

#include "sphere.hpp"

int Sphere::counter {0};//need to be define
double const Sphere::PI {3.14159};
double Sphere::vol(double r) { return (4.0*PI*r*r*r)/3.0; }
int Sphere::ctr()            { return counter; }
