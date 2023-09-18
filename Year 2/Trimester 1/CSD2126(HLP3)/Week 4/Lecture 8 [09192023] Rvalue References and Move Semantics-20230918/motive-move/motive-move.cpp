// CSD2125/CS225 05/22/2018
// This source file uses class Str to illustrate move semantics.
// To see move semantics in action (without NRVO), compile like this:
// g++ -std=c++17 -D=_DEBUG -fno-elide-constructors str.cpp motive-move.cpp -o str17-noelide.out
// Run and see count of Str ctors invoked: ./str17-noelide.out > str17-noelide.txt
// This should print a count of 6 Str ctors being invoked.
// Now, compile with NRVO like this:
// g++ -std=c++17 -D=_DEBUG str.cpp motive-move.cpp -o str17-elide.out
// Run and see count of Str ctors invoked: ./str17-elide.out > str17-elide.txt
// You should see RVO in action with the count of Str ctors reduced to 5

#include <iostream>
#include <vector>
#include <string>
#include "str.h"

std::vector<Str> f() {
  std::vector<Str> w;
  w.reserve(3);
  Str s = "data";

  w.push_back(s);
  w.push_back(s+s);
  w.push_back(std::move(s));
  std::cout << "---------------------------1-----------------\n";

  return w;
}

int main() {
  std::vector<Str> v;
  // useless stuff ...
  std::cout << "v.size(): " << v.size() << "\n";  
  v = f();
  std::cout << "--------------------------2-----------------\n";
  for (Str const& s : v) {
    std::cout << s << "\n";
  }
  std::cout << "Str::Count(): " << Str::Count() << "\n";
}
