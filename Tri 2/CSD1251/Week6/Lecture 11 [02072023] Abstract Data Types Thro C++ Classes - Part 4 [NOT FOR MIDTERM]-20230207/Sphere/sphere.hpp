// HLP2
// Interface file to illustrate static data members and member functions
// See the handout for more details

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>
#include <string>

class Sphere {
public:
  //Sphere(double r) : radius(r), volume((4.0*PI*r*r*r)/3.0) { ++counter; }//single argument conversion constructor
  //convert and create a sphere object
  explicit Sphere(double r) : radius(r), volume((4.0*PI*r*r*r)/3.0) { ++counter; }
  Sphere (Sphere const& rhs) : radius(rhs.radius), volume(rhs.volume){}//copy constructor. If not created, compiler will make one for you. If define, will use the defien one 

  operator double() const {return (4.0*PI*radius*radius*radius)/3.0; }//Implicit type conversion operator. Take sphere and convert it to double
  operator std::string() const {return std::to_string((4.0*PI*radius*radius*radius)/3.0); }//Implicit type conversion operator. Take sphere and convert it to string
  //dont return by ref, this is tem, when the function ends, it dies
  ~Sphere() { --counter; }//destructor. Decrement counter before dying
  
  double Radius() const   { return radius; }//pointer to a Read only
  void   Radius(double r) { radius = r; volume = (4.0*PI*r*r*r)/3.0; }//pointer to a sphere
  double Volume() const   { return vol(radius); }

  //Static member function
  //Use to check if "anoyone is alive"
  //Does not take a this* pointer
  static double vol(double r);
  static int    ctr();
private:
  //16 byte 
  double radius, volume;//Keep track of value of sphere
  static int counter;//static global variable. All can see.Only one exist 
  static double const PI;

  //take all data function and place it in data. 
};

#endif // #ifdef SPHERE_HPP
