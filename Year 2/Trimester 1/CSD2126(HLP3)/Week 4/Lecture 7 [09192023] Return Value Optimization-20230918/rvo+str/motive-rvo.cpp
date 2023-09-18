// CSD2125/CS225 05/22/2018
#include <iostream>
#include <vector>
#include <string>
#include "str-98.h"
// to see NRVO in action, first compile without copy elision like this:
// g++ -std=c++98 -D=_MY_DEBUG -fno-elide-constructors str-98.cpp motive-rvo.cpp -o str98-noelide.out
// Run and see count of Str ctors invoked: ./str98-noelide.out > str98-noelide.txt
// This should print a count of 13 Str ctors being invoked because of the unnecessary
// copies of unnamed std::vector<Str> objects being constructed on the stack as return objects.
// Now, compile with RVO like this:
// g++ -std=c++98 -D=_MY_DEBUG str-98.cpp motive-rvo.cpp -o str98-elide.out
// Run and see count of Str ctors invoked: ./str98-elide.out > str98-elide.txt
// You should see RVO in action with the count of Str ctors reduced to 5

// Now, repeat for -std=c++11.
// You'll see that without RVO, move semantics kick in for std::vector and reduce
// the number of Str ctors invoked from 13 to 6.
// You'll also see that the number of Str ctors invoked with RVO reduces to 5.
// These reductions come in thro' move semantics of the std::vector container.
// However, remember that move semantics are more expensive compared to RVO.

// Since RVO is part of C++17 standard, it cannot be disabled in C++17 with
// -fno-elide-constructors flag

std::vector<Str> f98() {
  std::vector<Str> w;
  w.reserve(3);
  Str s = "data";

  w.push_back(s);
  w.push_back(s+s);
  w.push_back(s);
  
  std::cout << "--------------------------1-----------------\n";

  return w;
}

int main() {
  std::vector<Str> v = f98();
  // useless stuff ...
  std::cout << "v.size(): " << v.size() << "\n";  
  std::cout << "--------------------------2-----------------\n";
  for (std::vector<Str>::const_iterator ci = v.begin(); ci != v.end(); ++ci) {
    std::cout << ci->c_str() << "\n";
  }
  std::cout << "Str::Count(): " << Str::Count() << "\n";
}
