// FilePtr is an RAII class that encapsulates a C file handle of type FILE*.
// CSD2125 09/28
#ifndef FILEPTR_H
#define FILEPTR_H

#include <cstdio>
#include <stdexcept>

class FilePtr {
  FILE *p;
public:
  FilePtr(char const *n, char const *a) : p{fopen(n, a)} {
    if (p == nullptr) throw std::runtime_error("FilePtr: Can't open file\n");
    // only print if ctor doesn't throw
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }

  // delegating ctor
  FilePtr(std::string const& n, char const *a) : FilePtr(n.c_str(), a) {}

  explicit FilePtr(FILE *pp) : p{pp} {
    if (p == nullptr) throw std::runtime_error("FilePtr: nullptr\n");
    // only print if ctor doesn't throw
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }

  // cannot make copy of FilePtr
  FilePtr(FilePtr const&) = delete;
  FilePtr& operator=(FilePtr const&) = delete;

  ~FilePtr() { 
    fclose(p);
#ifdef _DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  }

  // get raw C file handle ...
  operator FILE* () { return p; }
};

#endif
