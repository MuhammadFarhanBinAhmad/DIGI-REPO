// HLP2
// 02/07/2022
// Intro to class design and implementation by designing and
// implementing class Str that will encapsulate a C-string ...
// This interface file contains the current definition of class Str ...
#ifndef STR_HPP
#define STR_HPP

#include <cstddef>
#include <iostream>

namespace hlp2 {

class Str {
  // type definitions ...
public:
  using value_type      = char;
  using size_type       = size_t;
  using reference       = value_type&;
  using pointer         = value_type*;
  using const_reference = char const&;
  using const_pointer   = char const*;

  // interface
public:
  Str(); // default ctor
  Str(char const *rhs); // single-argument ctor
  Str(Str const& rhs); // copy ctor
  ~Str(); // dtor

  char& operator[](size_type idx);
  char const& operator[](size_type idx) const;

  bool empty() const;
  size_type size() const;

  //char const* c_str() const;
  friend std::ostream& operator<<(std::ostream& os, Str const& rhs);

// implementation details ...
private:
  size_type len;
  pointer ptr;
};

// non-member function
//std::ostream& operator<<(std::ostream& os, Str const& rhs);

} // end namespace hlp2

#endif
