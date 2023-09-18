// CSD2125/CS225 - 07/06
// Class design with null-terminated C-strings:
// Definition of class Str

#ifndef STR_H
#define STR_H

#include <cstddef>
#include <iostream>

class Str {
public:
  Str(); // default ctor
  Str(char const*); // conversion ctor
  Str(Str const&); // copy ctor
  ~Str(); // dtor

  Str& operator=(Str const& rhs); // copy assignment operator
  Str& operator=(char const* rhs); // copy assignment operator

  Str& operator+=(Str const& rhs);
  Str& operator+=(char const* rhs);

  char const& operator[](size_t idx) const { return ptr[idx]; }
  char& operator[](size_t idx)  { 
    return const_cast<char&>(static_cast<Str const&>(*this)[idx]);
  }

  // implicit type conversion operator
  //explicit operator char const* () const { return ptr; }
  char const* c_str() const { return ptr; }

  bool empty() const { return len; }
  size_t size() const { return len; }
  
  char* begin() {return ptr;}
  char* end()   {return ptr+len;}

  char const* begin() const {return ptr;}
  char const* end()   const {return ptr+len;}

  static size_t Count();

private:
  size_t len;
  char   *ptr;

  static size_t count;
};

Str operator+(Str const& lhs, Str const& rhs);
Str operator+(Str const& lhs, char const *rhs);
Str operator+(char const *lhs, Str const& rhs);

std::ostream& operator<<(std::ostream&, Str const&);

#endif
