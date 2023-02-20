// HLP2
// Driver file to illustrate use of static data members and member functions
// in class Sphere
// See the handout for more details

#include <iostream>
#include <string>
#include "sphere.hpp"

//void foo(Sphere s)// pass by value will make copy. call deconstrutor twice. Not effiecient
void foo(Sphere const& s)
{
  std::cout << "Whats the volume : " << s.Volume() << std::endl;
}
void boo(double d)
{
  std::cout << "What's d " << d << '\n';
}
void boo(std::string const& d)

{
  std::cout << "What's d " << d << '\n';
}
int main() {
  int x{10};//define and intitalize
  int y;//define but not initialize

Sphere x{3.0}, y{6.0};//define and initialize
Sphere z{x};//call copy constructor
y=x;//copy assignement

  //#if 1
  //foo(3.0);//Will look for declaration of foo. Which is the top one.But takes in sphere not double
  //Will convert as in sphere.hpp, can convert there (Sphere(double r)).
  //But if Sphere(double r) is explicit, this will NOT compile

  //foo(static_cast<Sphere>(3.0));//Althought not define, compiler will make a copy constructor for you when needed
  //the code will stright awa y call foo and not the copy constructor

  //Sphere s{3.0};

  std::cout << "anybody alive? " << (Sphere::ctr() ? "yes" : "no")<< '\n';
  //boo(s);
  // std::string x =s;
  // std::cout << "What's S?" <<(x)<< '\n';
  // boo(static_cast<std::string>(s));//implicit conversion
  // std::cout << "What's s " << s << '\n';
  //#else
  Sphere s1(3.0);
  std::cout << "s1 radius: " << s1.Radius() << " | volume: " << s1.Volume() << "\n";
  s1.Radius(5.0);
  std::cout << "s1 radius: " << s1.Radius() << " | volume: " << s1.Volume() << "\n";
  std::cout << "sizeof(Sphere): " << sizeof(Sphere) << "\n";
  std::cout << "   radius: " << 3.0         << " | volume: " << Sphere::vol(3.0) << "\n";
  std::cout << "How many Sphere's? " << Sphere::ctr() << "\n";
}
