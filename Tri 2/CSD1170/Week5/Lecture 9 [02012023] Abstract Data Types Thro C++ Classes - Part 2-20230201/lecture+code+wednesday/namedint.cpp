// HLP2
// 01/15/2022
// Example of a useful class NamedInt that is composed of a 
// well-defined user type [std::string] and a built-in type [int].
// The class is used to illustrate:
// 1) The idea and implementation of member-initialization lists.
// 2) Default copy construction, copy assignment.
// 3) Default destructor
// 4) When a default constructor is synthesized and what happens if
//    the class doesn't declare one.
// 5) Why there is no need to implement trivial copy constructor,
//    copy assignment, and destructor.
#include <iostream>
#include <string>

class NamedInt {
public:
  NamedInt() : name{},ival{0};//default constructor
  //NamedInt():name{},val{} {}//silly cause no name or val. 
  NamedInt(char const *nam, int val);
  NamedInt(std::string const& nam, int val);
  
  NamedInt(NamedInt const&)            = default;
  NamedInt& operator=(NamedInt const&) = default;
	~NamedInt()                          = default;

  //Get and setter
  std::string const& Name() const;
  std::string&       Name();
  int const&         Int() const;
  int&               Int();
private:
  std::string name;
  int ival;
};
#if 0
// example of member initializer list!!!
//Initialize always take place in the order of declaration
//eg.nam will be initilze first, then val. If switch place, name will still be initialize first
NamedInt::NamedInt(char const *nam, int val) : name{nam}, ival{val} {
  // empty by design
  //THIS IS INITIALIZE
}
#else 
NamedInt::NamedInt(char const *nam, int val) : name{nam}, ival{val} {
  name = nam;//this is ASSIGNMENT
  //memory need to be initialze for this string
}
#endif
NamedInt::NamedInt(std::string const& nam, int val) : name{nam}, ival{val} {
  // empty by design
}

std::string const& NamedInt::Name() const { return name; }
std::string&       NamedInt::Name()       { return name; }

int const&         NamedInt::Int() const { return ival; }
int&               NamedInt::Int()       { return ival; }

// overload operator << to write NamedInt to output stream ...
std::ostream& operator<<(std::ostream& os, NamedInt const& rhs) {
  os << '(' << rhs.Name() << ", " << rhs.Int() << ')';
  return os;
}

int main() {

  int *pin20 = new NamedInt[2000];//will intilize but need default construct
std::vector<NamedInt> highscores
highscores.reseve(20);//will reserve BUT wont initialize

  NamedInt ni1{"1st Prime Number", 2};//initialize as a empty string. the string inside need to be allocated inside. But constrictor already one already initalize. thus another need to be created to hold new string
  NamedInt ni2{ni1}; // copy constructor generated
  NamedInt ni3{"2nd Prime Number", 3};
  ni2 = ni3;         // copy assignment generated
  std::cout << "ni1: " << ni1 << " | ni2: " << ni2 << " | ni3: " << ni3 << '\n';
}