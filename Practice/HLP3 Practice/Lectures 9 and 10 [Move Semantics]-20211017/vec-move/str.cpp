/*
CSD 2125
Class design with null-terminated C-strings:
improving previous version with static members, initializer_list and move semantics.

Definition of member functions of class Str
*/

#include "str.h"
#include <iostream>
#include <cstring>

size_t Str::copy{}; // define static variable
size_t Str::CopyCount() { return copy; }
size_t Str::move{}; // define static variable
size_t Str::MoveCount() { return move; }

inline void Str::swap(Str& rhs) noexcept {
  std::swap(len, rhs.len);
  std::swap(ptr, rhs.ptr);
}

inline void swap(Str& lhs, Str& rhs) noexcept {
  lhs.swap(rhs);
}

Str::Str() {
  ++copy;
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << len << ">\n";
#endif  
}

Str::Str(char const *s) : len{std::strlen(s)}, ptr{new char [len+1]} {
  ++copy;
  std::strcpy(ptr, s);
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << ptr << ">\n";
#endif
}

Str::Str(Str const& rhs) : len{rhs.len}, ptr{new char [len+1]} {
  ++copy;
  std::strcpy(ptr, rhs.ptr);
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << ptr << ">\n";
#endif
}

Str::Str(std::initializer_list<char> rhs) : len{rhs.size()}, ptr{new char [len+1]} {
  ++copy;
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << ptr << ">\n";
#endif
}

Str::~Str() {
  //--count;
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << (ptr?ptr:"nullptr") << ">\n";
#endif

  delete [] ptr;
}

// exception safe
Str& Str::operator=(Str const& rhs) {
  Str copy{rhs};
  swap(copy);
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << ptr << ">\n";
#endif
  return *this;
}

Str& Str::operator=(char const *rhs) {
  Str copy{rhs};
  swap(copy);
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << ptr << ">\n";
#endif
  return *this;
}

#ifdef STR_MOVE
Str::Str(Str&& rhs) noexcept : len{rhs.len}, ptr{rhs.ptr} {
  ++move;
  rhs.ptr = nullptr;
#ifdef STR_DEBUG
std::cout << __PRETTY_FUNCTION__ << " <" << len << ">\n";
#endif  
}

Str& Str::operator=(Str&& rhs) noexcept {
  ++move;
  if (this != &rhs) {
    //swap(rhs);
    // the swap is better - but it is commented out to show you
    // how *this is "stealing" the resources of rhs ...
    len = rhs.len;
    delete [] ptr;
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
  }
#ifdef STR_DEBUG
  std::cout << __PRETTY_FUNCTION__ << " <" << len << ">\n";
#endif  
  return *this;
}
#endif

Str& Str::operator+=(Str const& rhs) {
  size_t tmp_len = len + rhs.len;
  char   *tmp_ptr {new char [tmp_len+1]};
  std::strcpy(tmp_ptr, ptr);
  std::strcat(tmp_ptr, rhs.ptr);

  len = tmp_len;
  delete [] ptr;
  ptr = tmp_ptr;

  return *this;
}

Str& Str::operator+=(char const* rhs) {
  size_t tmp_len = len + std::strlen(rhs);
  char   *tmp_ptr {new char [tmp_len+1]};
  std::strcpy(tmp_ptr, ptr);
  std::strcat(tmp_ptr, rhs);

  len = tmp_len;
  delete [] ptr;
  ptr = tmp_ptr;

  return *this;
}

Str& Str::operator+=(char ch) {
  size_t tmp_len = len + 1;
  char *tmp_ptr {new char [tmp_len+1]};
  std::strcpy(tmp_ptr, ptr);
  tmp_ptr[len] = ch;
  tmp_ptr[len+1] = '\0';

  len = tmp_len;
  delete [] ptr;
  ptr = tmp_ptr;
  return *this;
}

void Str::push_back(char ch) {
  *this += ch;
}

// non-member functions ...
Str operator+(Str const& lhs, Str const& rhs) {
  Str tmp{lhs};
  tmp += rhs;
  return tmp;
}

Str operator+(Str const& lhs, char const *rhs) {
  Str tmp{lhs};
  tmp += rhs;
  return tmp;
}

Str operator+(char const *lhs, Str const& rhs) {
  Str tmp{lhs};
  tmp += rhs;
  return tmp;
}

std::ostream& operator<<(std::ostream& os, Str const& rhs) {
  os << rhs.c_str();
  return os;
}
