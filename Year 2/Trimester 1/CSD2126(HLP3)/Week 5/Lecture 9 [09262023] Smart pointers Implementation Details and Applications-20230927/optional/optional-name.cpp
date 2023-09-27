// HLP3: 09/23/2023
// optional-name.cpp: The following program provides another example in using
// std::optional<> for the optional passing of arguments and/or the optional
// setting of a data member.

#include <iostream>
#include <string>
#include <optional>

/*
Class Name represents a name that consists of a first name, an optional
middle name, and a last name.
The member middle is defined accordingly and the constructor allows you to
pass std::nullopt when there is no middle name. This is a different state
than the middle name being the empty string.
*/
class Name {
public:
  Name (std::string fn, std::optional<std::string> mn, std::string ln)
  : first{std::move(fn)}, middle{std::move(mn)}, last{std::move(ln)} {}

  /*
  Note also that std::optional<> changes the syntactic usage of the value
  of data member middle.
  Using n.middle as a Boolean expression yields whether there is a middle name. 
  *n.middle is used to access the current value (if there is one).
  */
  friend std::ostream& operator<<(std::ostream& os, Name const& n) {
    os << n.first << ' ';
#if 0
    if (n.middle) {   // print middle name or nothing ...
      os << *n.middle << ' ';
    } 
    // Another option for accessing the value is by using member function 
    // value_or(), which enables you to specify a fallback value in case
    // no value exists.
#else
    os << n.middle.value_or("") << ' '; // print middle name or nothing ...
#endif

    return os << n.last;
  }

private:
  std::string first;
  std::optional<std::string> middle;
  std::string last;
};

int main() {
  Name n{"Clint", std::nullopt, "Eastwood"};
  std::cout << n << '\n';
  Name m{"Uma", "Karuna", "Thurman"};
  std::cout << m << '\n';
}