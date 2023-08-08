#include <iostream>
#include <cstring>
#include <string>

template <typename T>
T const& Max(T const& a, T const& b, T const& c) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return a;
}

// maximum of two values of any type
template <typename T>
T Max(T lhs, T rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return rhs < lhs ? lhs : rhs;
}

// maximum of two pointers
template <typename T>
T* Max(T *lhs, T *rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return *rhs < *lhs ? lhs : rhs;
}

// maximum of two C-strings
char const* Max(char const *lhs, char const *rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return std::strcmp(rhs, lhs) < 0 ? lhs : rhs;
}

int main() {
  char const *px = "tic";
  char const *py = "tac";
  char const *pz = "toe";
  Max(px, py, pz);

  return 0;
  int a{7}, b{42};
  auto m1 = Max(a, b); // Max for two values of type int

  int ca{7}, cb{42};
  auto mc1 = Max(a, b); // Max for two values of type int const

  std::string s1{"hey"}, s2{"you"};
  auto m2 = Max(s1, s2); // Max for two values of type std::string

  int *pa{&a}, *pb{&b};
  auto m3 = Max(pa, pb); // Max for two pointers

  int const *pra{&a}, *prb{&b};
  auto mr3 = Max(pra, prb); // Max for two int const*

  char const *pca{"hello"}, *pcb{"world"};
  auto m4 = Max(pca, pcb); // Max for two C-strings
}