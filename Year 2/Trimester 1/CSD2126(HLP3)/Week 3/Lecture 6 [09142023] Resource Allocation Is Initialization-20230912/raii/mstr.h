// CSD2125/CS225 09/28
// Definition of class MStr illustrates an RAII class that encapsulates
// C-strings using dynamically allocated free store memory.
// Pay special attention to the ctor that illustrates how to
// enclose the member initialization list in a try block.

#ifndef MSTR_H
#define MSTR_H

#include <cstddef>
#include <iostream>

class MStr {
public:
  MStr(); // default ctor
  MStr(char const*); // conversion ctor
  MStr(size_t n, char ch);
  ~MStr(); // dtor

  static size_t Count();

private:
  size_t len;
  char   *ptr;

  static size_t count;
};

#endif
