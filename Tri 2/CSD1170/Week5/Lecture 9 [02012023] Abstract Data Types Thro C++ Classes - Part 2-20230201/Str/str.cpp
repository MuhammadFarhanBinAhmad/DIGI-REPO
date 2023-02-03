// HLP2
// 02/07/2022
// Intro to class design and implementation by designing and
// implementing class Str that will encapsulate a C-string ...
// Implementation file that contains definitions of member
// function declared in class Str [in interface file str.hpp] ...

#include "str.hpp"
#include <cstring>

namespace hlp2 {

Str::Str() : len{0}, ptr{new char[len+1]{'\0'}} {
  // empty by design ...
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Str::Str(char const *rhs) : len{std::strlen(rhs)}, ptr{new char [len+1]} {
  std::strcpy(ptr, rhs);
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Str::Str(Str const& rhs) : len{rhs.len}, ptr{new char [len+1]} {
  std::strcpy(ptr, rhs.ptr);
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Str::~Str() {
  delete[] ptr;
}

Str::reference Str::operator[](Str::size_type idx) {
  return ptr[idx];
}

Str::const_reference Str::operator[](Str::size_type idx) const {
  return ptr[idx];
}

bool Str::empty() const {
  return this->len==0 ? true : false;
}

size_t Str::size() const {
  return this->len;
}

#if 0
char const* Str::c_str() const {
  return ptr;
}
#endif

std::ostream& operator<<(std::ostream& os, Str const& rhs) {
  //os << rhs.c_str();
  os << rhs.ptr;
  return os;
}


} // end namespace hlp2