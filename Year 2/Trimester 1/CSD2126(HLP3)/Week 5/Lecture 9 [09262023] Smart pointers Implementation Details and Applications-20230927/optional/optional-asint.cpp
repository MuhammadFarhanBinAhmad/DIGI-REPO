// HLP3: 09/23/2023
// optional-asint.cpp: The following program demonstrates some abilities 
// of std::optional<> by using it as a return value.

#include <iostream>
#include <string>
#include <optional>

/*
This program defines a function as_int() to convert a passed string into an
integer. However, this might not succeed. Therefore, a std::optional<> is used
so that we can return "no int" instead of defining a special int value for this
return value or throwing an exception to the caller.
Thus, we either return the result of calling std::stoi, which initializes the
return value with an int, or we return std::nullopt, signaling that we do not
have an int value.
*/

// convert string to int if possible:
#if 1
std::optional<int> as_int(std::string const& s) {
  try {
    return std::stoi(s);
  } catch (...) {
    return std::nullopt; // signals that there is no int
  }
}
#else
// above function can also be implemented as:
std::optional<int> as_int(std::string const& s) {
  std::optional<int> ret; // initially no value
  try {
    ret = std::stoi(s);
  } catch (...) {
  }
  return ret;
}
#endif

int main() {
  for (std::string s : {"42", " 077", "hello", "0x33"} ) {
    // try to convert s to int and print the result if possible:
    std::optional<int> oi{as_int(s)};
    /*
    For each returned std::optional<int> oi, we evaluate whether we have a
    value [by evaluating the object as a Boolean expression] and access the
    value by "dereferencing" the optional object:
    */
    if (oi) {
      std::cout << "Converting \"" << s << "\" to int: " << *oi << '\n';
    } else {
      std::cout << "Cannot convert \"" << s << "\" to int\n";
    }
  }

  /*
  There are alternative ways to implement the handling of the return value.
  Here, has_value() is used to check whether a value was returned, while
  value() is used to access the value.
  value() is safer than operator *: it throws an exception if no value exists.
  Operator * should be used only when you are sure that the optional contains
  a value, otherwise your program will have undefined behavior.
  */
  std::string s2{"  304 "};
  std::optional<int> oi = as_int(s2);
  if (oi.has_value()) {
    std::cout << "Converting \"" << s2 << "\" to int: " << oi.value() << '\n';
  }
}
