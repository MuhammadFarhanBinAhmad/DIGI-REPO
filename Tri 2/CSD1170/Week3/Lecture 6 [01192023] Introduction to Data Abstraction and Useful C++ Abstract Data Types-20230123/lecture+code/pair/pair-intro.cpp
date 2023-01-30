// HLP2: pair-intro.cpp
// 01/24/2022
// The following code illustrates the use of type std::pair to treat two values
// as a single unit. This class is used in several places in the standard
// library and is quite useful when programmers wish to return two values.
// In principle, you can create, copy, assign, and compare a pair<>.
// <utility> also provides a convenience function make_pair() to create a
// value pair without writing the types explicitly. 

#include <iostream>
#include <utility>

int main() {
  // make a pair of C-string and double values ...
  std::pair<char const*, double> p1{"pi", 3.14};
  
  // direct access to the corresponding members of a pair p1 is provided
  // by p1.first and p1.second ...
  std::cout << p1.first << " " << p1.second << '\n';

  // direct access to corresponding members of pair p1 is provided by an index.
  // You can get reference to p1.first using std::get<0>(p1) and
  // reference to p1.second using std::get<1>(p1)
  std::cout << std::get<0>(p1) << " " << std::get<1>(p1) << '\n';

  // make a pair of a pair<char,int> and double ...
  using PCI = std::pair<char, int>; // PCI is alias for type std::pair<char, int>
  std::pair<PCI, double> p2{PCI{'a', 1}, 1.21};
  std::cout << std::get<0>(p2).first << ' ' 
            << p2.first.second << ' ' << p2.second << '\n';

  // <utility> also provides a convenience function make_pair to
  // create a value pair without writing the types explicitly. 
  std::pair<int, double> p3 = std::make_pair(12, 12.123);
  std::cout << std::get<0>(p3) << " " << std::get<1>(p3) << '\n';

  int i{12};
  double d{12.123};
  std::pair<int, double> p4 = std::make_pair(i, d);
  std::cout << std::get<0>(p4) << " " << std::get<1>(p4) << '\n';
}
