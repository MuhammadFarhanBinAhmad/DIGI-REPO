// HLP2 04/01/2022
// non-modifying.cpp
// Here we look at algorithms that enable you to access elements without
// modifying the their values or changing their order.
// 1) Counting elements [covered here]
// 2) Minimum and maximum [covered here]
// 3) Searching elements [covered here]
// 4) Testing equality [covered here]
// 6) for_each algorithm [covered]

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cmath>
#include <set>

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

// fill values from first to last [both inclusive] into collection ...
template <typename Cont>
void insert_elements(Cont& coll, int first, int last) {
  for (; first <= last; ++first) {
    coll.push_back(first);
  }
}

// function object that defines a unary predicate for comparing
// each element in a sequence with a initial value ... 
template <typename T>
class GreaterThan {
public:
  GreaterThan(T const& v) : val{v} {}
  bool operator()(T const& v) const { return v > val; }
private:
  T val;
};

// function object that defines a unary function for multiplying
// a value with an initial value ...
template <typename T>
class MultiplyWith {
public:
  MultiplyWith(T const& v) : val{v} {}
  T operator()(T const& v) const { return v*val; }
private:
  T val;
};

// function object that replaces each element by its square ...
template <typename T>
struct Square {
  T operator()(T x) const { return x*x; }
};

// function object to determine if value is even
struct Even {
  bool operator()(int x) const { return !(x%2); }
};

// function object to compare absolute values of int values
struct AbsLess {
  bool operator()(int x, int y) const { return std::abs(x) < std::abs(y); }
};

// function object to compare two ints value as both even or both odd
struct BothEvenOrOdd {
  bool operator()(int x, int y) const { return x%2 == y%2; }
};

class SumAvg {
private:
  int total{};
  int count{};
public:
  double avg() const { return static_cast<double>(total)/count; }
  void operator()(int x) { total += x; ++count; }
};

} // end anonymous namespace

int main() {
// Counting elements 1: count, count_if
// difference_type count(InputIterator first, InputIterator last, T& value);
// difference_type count_if(InputIterator first, InputIterator last, UnaryPredicate op)
// The first form counts elements in range [first, last) that are equal to value.
// The second form counts elements in range [first, last) for whcih op(elem) is true.

  std::vector<int> v1;
  insert_elements(v1, 1, 9);
  print(v1, "v1: ");
// count values with value 4:
  std::cout << std::count(std::begin(v1), std::end(v1), 4) << "\n";
// count values that are even:
  std::cout << std::count_if(std::begin(v1), std::end(v1), Even{}) << "\n";

// Minimum and maximum: min_element, max_element, minmax_element
// ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
// ForwardIterator min_element(ForwardIterator first, ForwardIterator last, CompFunc op)
// ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
// ForwardIterator max_element(ForwardIterator first, ForwardIterator last, CompFunc op)
// pair<ForwardIterator,ForwardIterator>
// minmax_element(ForwardIterator first, ForwardIterator last)
// pair<ForwardIterator,ForwardIterator>
// minmax_element(ForwardIterator first, ForwardIterator last, CompFunc op)
// These algorithms return the position of the minimum element, maximum element, or
// a pair of the minimum and maximum element in range [first, last).
// The version without the op compare the elements with operator<.
// The version with op compare the elements with op(elem1, elem2) which will return
// true if elem1 is less than elem2.

  std::vector<int> v2;
  insert_elements(v2, 2, 6);
  insert_elements(v2, -3, 6);
  print(v2, "v2: ");
  std::cout << "minimum: " << *min_element(std::begin(v2), std::end(v2)) << "\n";
  std::cout << "maximum: " << *max_element(std::begin(v2), std::end(v2)) << "\n";
  using VICI = std::vector<int>::const_iterator;
  std::pair<VICI,VICI> min_max = minmax_element(std::begin(v2), std::end(v2), AbsLess{});
  std::cout << "minimum of absolute values: " << *min_max.first << "\n";
  std::cout << "maximum of absolute values: " << *min_max.second << "\n";

// Search first matching element: find, find_if
// InputIterator find(InputIterator first, InputIterator last, T const& value)
// InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate op)
// The first form returns the position of the first element in range [first, last) that
// has a value equal to value.
// The second form returns the position of the first element in range [first, last) for
// which the unary predicate op(elem) returns true.

  std::vector<int> v3;
  insert_elements(v3, 1, 9);
  insert_elements(v3, 1, 9);
  print(v3, "v3: ");

// find first element with value 4
  std::vector<int>::iterator pos1 = std::find(std::begin(v3), std::end(v3), 4);
  std::vector<int>::iterator pos2 = std::end(v3);
// find second element with value 4
  if (pos1 != std::end(v3)) {
    pos2 = std::find(++pos1, std::end(v3), 4);
    --pos1;
  }
// print all elements from first to second 4 [both included]:
  if (pos1 != std::end(v3) && pos2 != std::end(v3)) {
    std::copy(pos1, ++pos2, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
  }

// find first element greater than 3
  pos1 = std::find_if(std::begin(v3), std::end(v3), GreaterThan<int>{3});
  if (pos1 != std::end(v3)) {
    std::cout << "element " << std::distance(std::begin(v3), pos1) << " is first greater than 3\n";
  }

// Testing equality of ranges: equal
// bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
// bool equal(InputIterator1 first1, InputIterator1 last1, 
//           InputIterator2, BinaryPredicate op)
// The first form returns true if elements in range [first1, last1) are equal to
// elements in range starting with first2
// The second form returns true if each call of op(elem1, elem2) is true

  std::vector<int> v4, v5;
  insert_elements(v4, 1, 7);
  insert_elements(v5, 3, 9);

// check whether collections v4 and v5 are equivalent ...
  if (std::equal(std::begin(v4), std::end(v4), std::begin(v5))) {
    std::cout << "v4 == v5\n";
  } else {
    std::cout << "v4 != v5\n";
  }

// check whether corresponding elements of v4 and v5 are both even or both odd ...
  if (std::equal(std::begin(v4), std::end(v4), std::begin(v5), BothEvenOrOdd{})) {
    std::cout << "Even and odd elements of containers v3 and v4 correspond\n";
  } else {
    std::cout << "Even and odd elements of containers v3 and v4 don't correspond\n";
  }

// for_each algorithm: can be used to access and process each element in a range ...

// compute average of elements of a container ...
  std::vector<int> v6{5, 4, 6, 3, 7, 2, 10, 8, 1, 9};
  print(v6, "v6: ");
  SumAvg result = std::for_each(std::begin(v6), std::end(v6), SumAvg{});
  std::cout << "avg(v6): " << result.avg() << "\n";

  std::list<int> l6{5, 4, 6, 3, 7, 2, 10, 8, 1, 9};
  print(l6, "l6: ");
  result = std::for_each(std::begin(l6), std::end(l6), SumAvg{});
  std::cout << "avg(l6): " << result.avg() << "\n";

  std::multiset<int> s6{5, 4, 6, 3, 7, 2, 10, 8, 1, 9};
  print(s6, "s6: ");
  result = std::for_each(std::begin(s6), std::end(s6), SumAvg{});
  std::cout << "avg(s6): " << result.avg() << "\n";
}
