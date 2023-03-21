// HLP2 04/01/2022
// mutating.cpp
// Mutating algorithms change the order of element but not their values.
// Because elements of associative containers have an order defined by
// the container, you can't use these algorithms  as a destination for
// mutating algorithms.
// Out of the many mutating algorithms, we'll look at std::reverse and
// std::reverse_copy
//
// NOTE: Both lists and forward_lists provide an equivalent member function,
// reverse, which offers better performance because it relinks pointers
// instead of assigning element values.

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cmath>

namespace {

// function object to generate increasing values incrementally ...
template <typename T>
class IntGen {
public:
  IntGen(T v = T()) : val{v} {}
  T operator()() { T old_val{val}; ++val; return old_val; }
private:
  T val{};
};

template <typename Cont>
void print(Cont const& coll, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << postfix;
}

} // end anonymous namespace ...

int main() {
// Reversing order of elements algorithm 1a: reverse
// void reverse(BidirectionalIterator first, BidirectionalIterator last)
// Reverses the order of elements in range [first, last)
// sort guarantees a good performance (n-log-n) on average.

// write sequential values starting from 10 to v1's elements
  std::vector<int> vec(5);
  std::generate(std::begin(vec), std::end(vec), IntGen<int>(10));
  print(vec, "vec: ");
  std::reverse(std::begin(vec), std::end(vec));
  print(vec, "vec: ");

// Reversing order of elements while copying them algorithm 1b: reverse_copy
// OutputIterator
// reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
//              OutputIterator dest)
// Reverse the order of the elements while copying them from the source range
// [first, last) to the destination range starting with dest
// Returns the position after the last copied element in the destination range
// The caller must ensure that destination range is big enough or that
// insert iterator are used:

// reverse elements in vec into a linked list
  std::list<int> lst; // empty container ...
  std::reverse_copy(std::begin(vec), std::end(vec), std::back_inserter(lst));
  print(lst, "lst: ");

// reverse elements in lst using member function reverse:
  lst.reverse();
  print(lst, "lst: ");
}
