// CSD 2125/CS225 - 07/06
// Definition of member functions of class MStr encapsulating null-terminated
// C-strings. This class will be used to illustrate RAII principles.

#include "mstr.h"
#include <iostream>
#include <cstring>

size_t MStr::count = 0; // definition of static data member

// definition of static member function
size_t MStr::Count() { return count; }

MStr::MStr() : len{0}, ptr{new char [len+1]} {
  ++count;

  *ptr = '\0';

#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

MStr::MStr(char const *s) : len{std::strlen(s)}, ptr{new char [len+1]} {
  ++count;

  std::strcpy(ptr, s);

#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

// this ctor might throw - therefore, and we need a try-catch block
// in the ctor 
MStr::MStr(size_t n, char ch) try : // like a try { ... } block
  len{n}, ptr{new char [len+1]} {
  // body of ctor
  ++count;
  for (size_t i{}; i < len; ++i) {
    ptr[i] = ch;
  }
  ptr[len] = '\0';
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
} catch (...) { // catch handler after ctor body
  std::cout << "MStr::MStr(size_t, char) throwing an error\n";
  throw;
}

MStr::~MStr() {
  --count;
#ifdef _DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif

  delete [] ptr;
}
