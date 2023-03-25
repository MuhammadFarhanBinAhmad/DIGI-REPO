// HLP2: adaptor-iter.cpp [pghali@digipen.edu]
// This source file illustrates the implementation of some commonly used
// STL algorithms: std::copy, std::for_each, std::find_if
// and the implementation of call-back functions and function objects ...

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>

template <typename Cont>
void print(Cont const& c, std::string const& pre, std::string const& pos="\n") {
  std::cout << pre;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << pos;
}

template <typename InIter, typename Function>
Function for_each(InIter first, InIter last, Function f) {
  while (first != last) {
    f(*first);
    ++first;
  }
  return f;
}

template <typename InIter, typename UnaryPredicate>
InIter find_if(InIter first, InIter last, UnaryPredicate f) {
  while (first != last) {
    if (f(*first)) return first;
    ++first;
  }
  return first;
}

template <typename InIter, typename OutIter>
OutIter copy(InIter src_beg, InIter src_end, OutIter dst_beg) {
  while (src_beg != src_end) {
    *dst_beg++ = *src_beg++;
  }
  return dst_beg;
}

// unary predicate
bool div_by_7(int x) {
  return (x%7 == 0) ? true : false;
}

// function template with template non-type parameter
template <int Value>
void add_value(int& x) {
  x += Value;
}

// this function can increment an integral value by 5 ...
void add_5(int& x) {
  x += 5;
}

// function object because this class overloads the function call operator
// anywhere you can use a function, you can use an object of this type
// with function-call semantics.
class AddValue {
private:
  int value_to_add;
public:
  AddValue(int v) : value_to_add(v) {}
  // this is the overload of () [function call] operator
  void operator() (int& x) const { x += value_to_add; }
};

int main() {
  std::vector<int> vi{5, 4, 6, 3, 7, 2, 10, 8, 1, 9};

  // use my find_if algorithm
  std::vector<int>::iterator it = ::find_if(vi.begin(), vi.end(), div_by_7);
  if (it != vi.end()) {
    *it *= *it;
  }
  print(vi, "vi: ");

  // use STL find_if
  it = std::find_if(vi.begin(), vi.end(), div_by_7);
  if (it != vi.end()) {
    *it /= *it;
  }
  print(vi, "vi: ");
  
  ::for_each(vi.begin(), vi.end(), add_5);
  print(vi, "vi: ");
  ::for_each(vi.begin(), vi.end(), add_value<-5>);
  print(vi, "vi: ");

  AddValue av(5);
  int to_add_to {6};
  av(to_add_to);
  std::cout << "to_add_to: " << to_add_to << "\n";

  ::for_each(vi.begin(), vi.end(), av);
  print(vi, "vi: ");
}
