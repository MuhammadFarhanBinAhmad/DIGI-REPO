#include "num.hpp"
#include <iostream>

// GETTING FUNCTION NAMES
#ifdef _MSC_VER
//#define PRINT_FUNCTION_NAME (__FUNCSIG__)
#define PRINT_FUNCTION_NAME (printf("\n||%s||\n", __FUNCSIG__))
#else // GNU, g++, clang++
//#define PRINT_FUNCTION_NAME (__PRETTY_FUNCTION__)
#define PRINT_FUNCTION_NAME (printf("\n||%s||\n", __PRETTY_FUNCTION__))
#endif
// __FUNCSIG__ and __PRETTY_FUNCTION__ both give char arrays / char*
// with a null byte at the end

Num::Num() {
  //val = -999;
  // empty by design
}

Num::Num(int v) {
  val = v;
  PRINT_FUNCTION_NAME;
}

#if 0
Num::Num(Num const& rhs) {
  val = rhs.val;
  PRINT_FUNCTION_NAME;
}

Num& Num::operator=(Num const& rhs) {
  val = rhs.val;
  PRINT_FUNCTION_NAME;
  return *this;
}
#endif

Num& Num::operator=(int rhs) {
  val = rhs;
  PRINT_FUNCTION_NAME;
  return *this;
}

Num& Num::operator+=(Num const& rhs) {
  this->val += rhs.val;
  PRINT_FUNCTION_NAME;
  return *this;
}

Num& Num::operator+=(int rhs) {
  val += rhs;
  PRINT_FUNCTION_NAME;
  return *this;
}

Num operator+(Num const& lhs, Num const& rhs) {
  Num tmp{lhs};
  tmp += rhs;
  PRINT_FUNCTION_NAME;
  return tmp;
}

Num operator+(Num const& lhs, int rhs) {
  Num tmp{lhs};
  tmp += rhs;
  PRINT_FUNCTION_NAME;
  return tmp;
}

Num operator+(int lhs, Num const& rhs) {
  Num tmp{lhs};
  tmp += rhs;
  PRINT_FUNCTION_NAME;
  return tmp;
}

int Num::get_val() const { PRINT_FUNCTION_NAME; return this->val; }
void Num::set_val(int v) { PRINT_FUNCTION_NAME; this->val = v; }

std::ostream& operator<<(std::ostream& os, Num const& rhs) {
  os << rhs.get_val();
  return os;
}
