#include <iostream>
#include <vector>
#include <string>
#include "str-98.h"
// to see NRVO in action, first compile without RVO like this:
// g++ -std=c++98 -D=_DEBUG -fno-elide-constructors str-98.cpp motive-rvo.cpp -o str98-noelide.out
// Run and see count of Str ctors invoked: ./str98-noelide.out > str98-noelide.txt
// This should print a count of 13 Str ctors being invoked because of the unnecessary
// copies of unnamed std::vector<Str> objects being constructed on the stack as return objects.
// Now, compile with RVO like this:
// g++ -std=c++98 -D=_DEBUG str-98.cpp motive-rvo.cpp -o str98-elide.out
// Run and see count of Str ctors invoked: ./str98-elide.out > str98-elide.txt
// You should see RVO in action with the count of Str ctors reduced to 5

// Now, repeat for -std=c++17.
// You'll see that move semantics kick in and reduce the number of Str ctors invoked
// without RVO enabled reduces from 13 to 6.
// You'll also see that the number of Str ctors invoked with RVO reduces to 5.
// The reduction comes in thro' move semantics of the std::vector container.
// However, remember that move semantics are more expensive compared to RVO.

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
