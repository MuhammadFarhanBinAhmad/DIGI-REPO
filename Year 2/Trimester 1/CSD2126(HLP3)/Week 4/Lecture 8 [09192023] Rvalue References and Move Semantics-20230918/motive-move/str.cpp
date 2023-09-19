// CSD2125/CS225 05/22/2018
// Definition of member functions of class Str

#include "str.h"
#include <iostream>
#include <cstring>

size_t Str::count = 0;
size_t Str::Count() { return count; }

Str::Str() : len{0}, ptr{new char [len+1]} {
  ++count;
  *ptr = '\0';
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

Str::Str(std::initializer_list<char> rhs) : len{rhs.size()}, ptr{new char [len+1]} {
  ++count;
  char *tmp_ptr {ptr};
  for (char ch : rhs) {
    *tmp_ptr++ = ch;
  }
  *tmp_ptr = '\0';
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

Str::Str(char const *s) : len{std::strlen(s)}, ptr{new char [len+1]} {
  ++count;
  std::strcpy(ptr, s);
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

Str::Str(Str const& rhs) : len{rhs.len}, ptr{new char [len+1]} {
  ++count;
  std::strcpy(ptr, rhs.ptr);
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

Str::Str(Str&& rhs) : len(rhs.len), ptr{rhs.ptr} {
  ++count;
  rhs.ptr = nullptr;
  rhs.len = 0;
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

Str::~Str() {
  //--count;
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  delete [] ptr;
}

// exception safe
Str& Str::operator=(Str const& rhs) {
  size_t tmp_len = rhs.len;
  char   *tmp_ptr = new char [tmp_len+1];
  std::strcpy(tmp_ptr, rhs.ptr);

  len = tmp_len;
  delete [] ptr;
  ptr = tmp_ptr;

#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif

  return *this;
}

Str& Str::operator=(Str&& rhs) {
  len = rhs.len;
  char *tmp_ptr {rhs.ptr};
  rhs.ptr = ptr;
  ptr = tmp_ptr;

#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif

  return *this;
}

Str& Str::operator=(char const *rhs) {
  size_t tmp_len = std::strlen(rhs);
  char   *tmp_ptr = new char [tmp_len+1];
  std::strcpy(tmp_ptr, rhs);

  len = tmp_len;
  delete [] ptr;
  ptr = tmp_ptr;

  return *this;
}

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
  //os << static_cast<char const*>(rhs);
  os << rhs.c_str();
  return os;
}
