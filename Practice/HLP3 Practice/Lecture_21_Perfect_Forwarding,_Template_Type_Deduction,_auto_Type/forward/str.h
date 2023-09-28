/*
CSD2125 10/05
Class design with null-terminated C-strings:
improving previous version with static members, initializer_list and move semantics.

Class definition
*/

#ifndef STR_H
#define STR_H

#include <cstddef>
#include <iostream>
#include <initializer_list>

class Str {
public:
  using value_type = char;
  using reference = char&;
  using const_reference = const char&;
  using pointer = char*;
  using pointer_reference = const char*;
  using iterator = char*;
  using const_iterator = const char*;
public:
  Str(); // default ctor
  Str(char const*); // conversion ctor
  Str(Str const&); // copy ctor
  Str(std::initializer_list<char>);
  ~Str(); // dtor

//#ifdef STR_MOVE
  Str(Str&& rhs) noexcept;
  Str& operator=(Str&& rhs) noexcept;
//#endif

  Str& operator=(Str const& rhs); // copy assignment operator
  Str& operator=(char const* rhs); // copy assignment operator
  Str& operator+=(Str const& rhs);
  Str& operator+=(char const* rhs);

  char const& operator[](size_t idx) const { return ptr[idx]; }
  char& operator[](size_t idx)  { 
    return const_cast<char&>(static_cast<Str const&>(*this)[idx]);
  }

  Str& operator+=(char ch);
  void push_back(char ch);

  // implicit type conversion operator
  //explicit operator char const* () const { return ptr; }
  char const* c_str() const { return ptr; }

  bool empty() const { return len; }
  size_t size() const { return len; }
  
  char* begin() {return ptr;}
  char* end()   {return ptr+len;}

  char const* begin() const {return ptr;}
  char const* end()   const {return ptr+len;}
  
  void swap(Str& rhs) noexcept;

  static size_t CopyCount();
  static size_t MoveCount();

private:
  size_t len{0};
  char   *ptr{new char [1]{'\0'}};

  static size_t copy;
  static size_t move;
};

Str operator+(Str const& lhs, Str const& rhs);
Str operator+(Str const& lhs, char const *rhs);
Str operator+(char const *lhs, Str const& rhs);

std::ostream& operator<<(std::ostream&, Str const&);
void swap(Str& lhs, Str& rhs) noexcept;

#endif
