// HLP2: list-iter.cpp [pghali@digipen.edu]
// This source file illustrates the following iterator functions:
// std::begin(), std::end()
// container::begin() and container::end()
// container::cbegin() and container::cend()
// container::rbegin() and container::rend()
// container::crbegin() and container::crend()
#include <forward_list>
#include <list>
#include <iostream>
#include <cctype>

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

int main() {
  std::list<char> lc;

  // append elements from 'a' to 'z'
  for (char ch{'a'}; ch <= 'z'; ++ch) {
    lc.push_front(ch);
  }

  // print all elements by iterating over all elements
  for (std::list<char>::const_iterator pos {lc.begin()}; pos != lc.end(); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << "\n";

  // initialize a singly-linked list with the contents of
  // doubly-linked list in REVERSE ORDER ...
  std::forward_list<char> sll{lc.rbegin(), lc.rend()};

  // print all elements of singly-linked list ...
  for (std::forward_list<char>::const_iterator pos{sll.begin()}; pos != sll.end(); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << "\n";

  // For containers, a range-based for loop is nothing but a convenience inteface,
  // which is defined to iterate over all elements of the passed range or container.
  // Within each loop body, the actual element is initialized by the value the
  // current iterator refers to.
  for (char ch : lc) {
    std::cout << ch << ' ';
  }
  std::cout << "\n";

  // if you use a nonconstant iterator and the type of the element is nonconstant,
  // you can change the values:
  for (std::list<char>::iterator pos {lc.begin()}; pos != lc.end(); ++pos) {
    *pos = std::toupper(*pos);
  }

  // Since C++11, standard containers provide member functions cbegin() and cend()
  // to return a constant iterator:
  for(std::list<char>::const_iterator pos {lc.cbegin()}; pos != lc.cend(); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << "\n";

  // Print doubly-linked list in REVERSE ORDER:
  for(std::list<char>::const_reverse_iterator pos {lc.crbegin()}; pos != lc.crend(); ++pos) {
    std::cout << *pos << ' ';
  }
  std::cout << "\n";
}
