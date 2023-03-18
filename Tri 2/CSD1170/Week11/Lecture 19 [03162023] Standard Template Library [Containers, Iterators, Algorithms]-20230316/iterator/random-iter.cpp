// HLP2: random-iter.cpp [pghali@digipen.edu]
// Illustrates pointer arithmetic with random access iterators ...

#include <vector>
#include <deque>
#include <iostream>
#include <string>

// print all elements of any container as long as the element type overloads
// the left-shift operator ...
template <typename Cont>
void print(Cont const& c, std::string const& pre, std::string const& pos="\n") {
  std::cout << pre;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << pos;
}

// change this to experiment with std::vector
using RandIntCont = std::deque<int>;

int main() {
  RandIntCont cont;

  // insert elements from -3 to 9
  for (int i {-3}; i <= 8; ++i) {
    cont.push_back(i);
  }

  // print number of elements by processing the distance between beginning and end
  std::cout << "number/distance: " << cont.end() - cont.begin() << "\n";

  // print all elements
  print(cont, "cont: ");

  // use operator [] rather than operator* to print elements
  for (RandIntCont::size_type i {0}; i < cont.size(); ++i) {
    if (i == 0) {
      std::cout << "cont: ";
    }
    std::cout << cont[i] << ' ';
  }
  std::cout << "\n";

  // print every second element ...
  for (RandIntCont::const_iterator pos = cont.cbegin(); pos < cont.cend()-1; pos += 2) {
    if (pos == cont.cbegin()) {
      std::cout << "cont: ";
    }
    std::cout << *pos << ' ';
  }
  std::cout << "\n";
}
