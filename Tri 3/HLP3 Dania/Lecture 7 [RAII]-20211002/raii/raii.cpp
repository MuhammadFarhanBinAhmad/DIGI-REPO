// Class X illustrates how to build a class that behaves like an RAII class simply
// using the has-a (containment) relationship with other RAII classes. Each of
// the contained RAII classes encapsulate the management of a single resource.
// Notice that exception safety is "automatically" built into local objects of type X
// by paying special attention to the ctors and dtor of the class.
// CSD2125 09/28
#include <iostream>
#include <exception>
#include <new>
#include <limits>
#include <string>
#include "mstr.h"
#include "fileptr.h"

class X {
public:
  FilePtr f; // deals with C file handle resource
  MStr    s; // deals with memory allocated thro' new []
public:
  X(char const *n, char const *a, char const *str) : f(n,a), s(str) {
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }
  X(char const *n, char const *a, size_t str_len, char ch) : f(n, a), s(str_len, ch) {
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }

  X(char const *n, char const *a, char const *str, size_t N) : X(n, a, str) {
    std::string s(N, 'a');
    throw std::length_error("ehll");
  }
  ~X() {
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }
};

int main() {
  X x1("file-out.txt", "w", "helloworld");
  std::cout << "--------------1--------------------\n";
  
  try {
    std::string tmp;
    X x2("file2-out.txt", "w", tmp.max_size(), 'a');
  } catch (...) {
    std::cout << "catching an exception\n";
  }

  std::cout << "----------------2------------------\n";

  try {
    X x2("file3-out.txt", "w", "today", 10);
  } catch (...) {
    std::cout << "Example of RAII even though ctor throws an exception\n";
  }
  std::cout << "----------------3------------------\n";
}
