// HLP2
// 01/15/2022
// Example of a class NamedRefIntConst that is composed of a 
// reference to well-defined user type [std::string] and a read-only
// built-in type [int].
// The class is used to illustrate:
// 1) The necessisity of member-initialization list for a constructor.
// 2) Why the default copy constructor may not be a good idea.
// 3) Why the compiler will refuse to synthesize a copy assignment.
// 4) How to tell the compiler to not synthesize both the
//    copy constructor and copy assignment.
#include <iostream>
#include <string>

class NamedRefIntConst {
public:
  // This ctor no longer takes a const name, because name is
  // now a reference-to-non-const string.
  NamedRefIntConst(std::string& name, int value);
  
  // The ctor with char const* as first parameter is gone, because
  // we must have a string to refer to

  NamedRefIntConst(NamedRefIntConst const&) = default;
  NamedRefIntConst& operator=(NamedRefIntConst const&) = default;

  // Assume no copy ctor nor copy assignment is declared ...
  std::string const& Name() const;
  std::string&       Name();
  int const&         Int() const;
private:
  std::string& name;  // this is now a reference
  int const ival;     // this is now const
};

NamedRefIntConst::NamedRefIntConst(std::string& nam, int val) : name{nam}, ival{val} {
  // empty by design
}

std::string const& NamedRefIntConst::Name() const { return name; }
std::string&       NamedRefIntConst::Name()       { return name; }

int const&         NamedRefIntConst::Int() const { return ival; }

// overload operator << to write NamedRefIntConst to output stream ...
std::ostream& operator<<(std::ostream& os, NamedRefIntConst const& rhs) {
  os << '(' << rhs.Name() << ", " << rhs.Int() << ')';
  return os;
}

int main() {
  std::string bmw("Beemer"), porsche("Porsche");
  NamedRefIntConst new_car(bmw, 2); // I've owned this car for 2 years
  NamedRefIntConst old_car(porsche, 5); // I've owned this car for 5 years

  // copy assignment is deleted and will therefore not compile:
  //new_car = old_car;
  std::cout << "new car: " << new_car << " | old_car: " << old_car << '\n';

  // copy construction is deleted and will therefore not compile:
  //NamedRefIntConst newest_car{old_car};
  //std::cout << "newest car: " << newest_car << '\n';
}