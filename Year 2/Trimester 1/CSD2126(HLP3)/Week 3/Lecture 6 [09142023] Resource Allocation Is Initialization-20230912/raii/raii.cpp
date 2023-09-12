// CSD2125/CS225 09/28
// Class X illustrates how to build a class that behaves like an RAII class
// simply using the has-a (containment) relationship with other RAII classes.
// Each of the contained RAII classes encapsulate the management of a single
// resource.
// Notice that exception safety is "automatically" built into local objects
// of type X by paying special attention to the ctors and dtor of the class.

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
  // CTOR #1 will be used as a delegating constructor
  // parameters for FilePtr [n: file name, a: file open mode]
  // parameter for MStr [str: C-style string]
  X(char const *n, char const *a, char const *str) : f(n,a), s(str) {
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }

  // CTOR #2
  // parameters for FilePtr [n: file name, a: file open mode]
  // parameters for MStr's fill ctor: [str_len: number of characters, ch: char to fill]
  X(char const *n, char const *a, size_t str_len, char ch) : f(n, a), s(str_len, ch) {
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }

  // CTOR #3
  // this ctor will delegate to first ctor
  // notice that this ctor intentionally throws an exception ...
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
  std::cout << "-----------------------------------\n";
  {
  X x1("file-out.txt", "w", "helloworld"); // calling CTOR #1
  }
  std::cout << "\n----------------------------------\n";

  try {
    std::string tmp;
    // x2's ctor will throw an exception because the ctor for its
    // data member s (of type MStr) will throw an exception!!!
    X x2("file2-out.txt", "w", tmp.max_size(), 'a'); // calling CTOR #2
  } catch (...) {
    std::cout << "Example of RAII: 1st data member f [of type FilePtr] is\n"
              << "constructed; 2nd data member s [of type MStr] throws an\n"
              << "exception but RAII ensures that f's dtor will be called.\n";
  }

  std::cout << "\n-----------------------------------\n";

  try {
    X x2("file3-out.txt", "w", "today", 10); // calling CTOR #3
  } catch (...) {
    std::cout << "Another example of RAII: Both data members f and s are constructed in x2's ctor.\n"
              << "Then, x2's ctor throws an exception. Hwoever, RAII will ensure that dtors for s\n"
              << "and f will called.\n";
  }
  std::cout << "\n-----------------------------------\n";
}
