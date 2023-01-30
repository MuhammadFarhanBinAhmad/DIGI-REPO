// HLP2
// 02/06/2022
// Interface file for a Student type that is used to introduce ADT
// development with classes as in handout+intro+classes.pdf

#ifndef STUDENT_HPP
#define STUDENT_HPP

// To implement function overloading and classes, function names are mangled.
// Both GNU and Microsoft C++ compilers contain macros to print the unmangled
// function name at runtime: GNU uses __PRETTY_FUNCTION__ macro while
// Microsoft provides __FUNCSIG__
// The following preprocessor directives check if the compiler is not GNU C++,
// and assigns the macro __PRETTY_FUNCTION__ to be equivalent to __FUNCSIG__ 
#if !(__GNUG__)
#define  __PRETTY_FUNCTION__ __FUNCSIG__
#endif

namespace hlp2 {

class Student {
public:
  Student(char const* log, int a, int y, double g); // ctor
  Student(Student const&); // copy ctor: define copy
  ~Student(); // dtor
  
  Student& operator=(Student const&); // copy assignment

  void set_login(const char* login); // mutators can't be const
  void set_age(int age);             // ditto
  void set_year(int year);           // ditto
  void set_gpa(double g);            // ditto
  
  char const* get_login() const; // accessors are nonmodifying
  int get_age() const;           // ditto
  int get_year() const;          // ditto
  double get_gpa() const;        // ditto

  void display() const; // ditto with display()
private:
  char *login; 
  int age, year;
  double gpa;
};

} // end namespace hlp2

#endif
