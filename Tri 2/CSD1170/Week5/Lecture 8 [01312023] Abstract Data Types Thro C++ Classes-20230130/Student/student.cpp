// HLP2
// 02/06/2022
// Implementation file for a Student type that is used to introduce ADT 
// development with classes as in handout+intro+classes.pdf
#include <iostream>
#include <cstring>
#include "student.hpp"

namespace hlp2 {

Student::Student(char const *log, int a, int y, double g) 
: login{nullptr}, age{a}, year{y}, gpa{g} {
  set_login(log);
}

Student::Student(Student const& rhs)
    : login{new char [std::strlen(rhs.login)+1]}, age{rhs.age}, 
      year{rhs.year}, gpa{rhs.gpa} {
  std::strcpy(login, rhs.login);
}

Student::~Student() {
  delete [] login;
}

Student& Student::operator=(Student const& rhs) {
  char *p = new char [std::strlen(rhs.login)+1]; // allocate new space
  std::strcpy(p, rhs.login);                     // copy login name
  delete [] login;                               // deallocate old space
  login = p;                            // now we can reset login
  age = rhs.age;
  year = rhs.year;
  gpa = rhs.gpa;
  return *this;                         // return a self-reference
}

void Student::set_login(char const *log) {
  delete [] login;
  login = new char[std::strlen(log) + 1]; 
  std::strcpy(login, log);
}

void Student::set_year(int y) {
  if ( (y < 1) || (y > 4) ) {
    std::cerr << "Error in year range!\n";
    year = 1;
  } else { year = y; }
}

void Student::set_age(int a) {
  if ( (a < 18) || (a > 100) ) {
    std::cout << "Error in age range!\n";
    age = 18;
  } else { age = a; }
}

void Student::set_gpa(double g) {
  if ( (g < 0.0) || (g > 4.0) ) {
    std::cout << "Error in GPA range!\n";
    gpa = 0.0;
  } else { gpa = g; }
}

void Student::display() const {
  std::cout << "login: " << login << "\n";
  std::cout << "  age: " << age << "\n";
  std::cout << " year: " << year << "\n";
  std::cout << "  GPA: " << gpa << "\n";
}

int Student::get_age()  const          { return age;}
int Student::get_year() const          { return year; }
double Student::get_gpa() const        { return gpa; }
char const* Student::get_login() const { return login; }

} // end namespace hlp2
