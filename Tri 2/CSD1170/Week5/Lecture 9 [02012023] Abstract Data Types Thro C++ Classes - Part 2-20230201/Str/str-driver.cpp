// HLP2
// 02/07/2022
// Intro to class design and implementation by designing and
// implementing class Str that will encapsulate a C-string ...
// This driver contains facilities to continually test the
// interface functions as they're added to class Str ...
// compile/link: g++ -std=c++17 str.cpp str-driver.cpp -o str.out

#include "str.hpp"
#include <iostream>

// convert lower-case characters to upper-case ...
void make_upper(hlp2::Str &rhs) {
  hlp2::Str::size_type str_len = rhs.size();
  for (hlp2::Str::size_type i{}; i < str_len; ++i) {
    rhs[i] = (rhs[i] >= 'a' && rhs[i] <= 'z') ? (rhs[i]-'a')+'A' : rhs[i];
  }
}

void foo() {
  hlp2::Str str1;
  hlp2::Str const str2{"hello"};
  hlp2::Str str3{str2}, str4 = hlp2::Str("world");

#if 0
  std::cout << "sizeof(str1): " << sizeof(str1) << " | sizeof(str2): " << sizeof(str2) << "\n";

  std::cout << "length of str1: " << str1.size() << "\n";
  std::cout << "length of str2: " << str2.size() << "\n";
#endif

  make_upper(str3);
  std::cout << "str1: " << str1 << " | str2: " << str2 << " | str3: " << str3 << "\n";

#if 0
  str1.size() => Str__size(&str1)

  size_t Str__size(Str const *this) {
    return (*this).len;
    return this->len;
  }
#endif
  //std::cout << "str2: " << str2 << '\n';
}

void boo() {
  foo();
}

int main() {
  boo();

}