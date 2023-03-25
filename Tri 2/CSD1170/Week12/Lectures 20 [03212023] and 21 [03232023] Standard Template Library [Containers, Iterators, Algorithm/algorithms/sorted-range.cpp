// HLP2 04/01/2022
// sorted-range.cpp
// This source file illustrates a few sorted-range algorithms which require
// that source ranges have elements sorted. These algorithms will have
// significantly better performance [logarithmic instead of linear complexity]
// than similar algorithms for unsorted ranges. Using these algorithms for 
// unsorted sequences will cause undefined behavior. 
// Associative containers provide special member functions for some search
// algorithms, e.g., find, lower_bound, and upper_bound.
// Here, we illustrate four useful sorted-range algorithms declared in <algorithm>:
// std::binary_search, std::lower_bound, std::upper_bound, std::equal_range, and std::merge
// Further, the following sample code illustrates a variety of function
// objects, binary function templates, a function template to print
// values of containers, and use of std::distance to get offset of a
// particular element from the sequence's first element.

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cmath>

namespace {

// function object for sorting criterion using absolute value
struct myLessAbs {
  bool operator()(int lhs, int rhs) const {
    return std::abs(lhs) < std::abs(rhs);
  }
};

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
  std::vector<int> v1(10);

// write sequential values starting from 10 to v1's elements so that
// container is sorted in ascending order ...
  std::generate(std::begin(v1), std::end(v1), IntGen<int>(10));
  print(v1, "v1: ");

// Sorted-range algorithm 1a: binary_search
// bool binary_search(ForwardIterator first, ForwardIterator last, T const& value)
// Returns true if sorted range [first, last) contains an element equal to value

// check existence of element with value 15
  if (std::binary_search(std::begin(v1), std::end(v1), 15)) {
    std::cout << "15 is present in sequence of values    : ";
  } else {
    std::cout << "15 is not present in sequence of values: ";
  }
  print(v1, "");

// check existence of element with value 55
  if (std::binary_search(std::begin(v1), std::end(v1), 55)) {
    std::cout << "55 is present in sequence of values    : ";
  } else {
    std::cout << "55 is not present in sequence of values: ";
  }
  print(v1, "");

// Instead of std::binary_search, we use std::set<T>::find(key) to find element
// with key ...
  using SIL = std::set<int,std::less<int>>;
  SIL si(std::rbegin(v1), std::rend(v1));
  print(si, "si: ");
// check existence of element with value 15 ...
  SIL::const_iterator sil_cit {si.find(15)};
  if (sil_cit != si.end()) {
    std::cout << *sil_cit << " exists in sequence of values: ";
  } else {
    std::cout           << "15 exists in sequence of values: ";
  }
  print(si, "");

// Sorted-range algorithm 1a: binary_search
// bool binary_search(ForwardIterator first, ForwardIterator last, 
//                    T const& value, BinaryPredicate op)
// Returns true if sorted range [first, last) contains an element equal to value
// where op is an optional binary predicate to be used as the sorting criterion:
  std::vector<int> v2{-3, 0, -3, 2, -3, 5, -3, 7, -0, -3, 5, -6, 8, 9, 0, 8, 7, -7, 8, 9, 3, -3, 2};
// first sort v2 using myLessAbs as sorting criterion
  std::sort(std::begin(v2), std::end(v2), myLessAbs{});
  print(v2, "v2: ");
// search for specific value -5 in v2 using same sorting criterion myLessAbs
// note: using any other sorting criterion will not be optimal!!!
  if (std::binary_search(std::begin(v2), std::end(v2), -5, myLessAbs{})) {
    std::cout << "-5 is present in container v2\n";
  } else {
    std::cout << "-5 is not present in container v2\n";
  }

// search for specific value 5 in v2 using same sorting criterion myLessAbs
  if (std::binary_search(std::begin(v2), std::end(v2), 5, myLessAbs{})) {
    std::cout << "5 is present in container v2\n";
  } else {
    std::cout << "5 is not present in container v2\n";
  }

// Sorted-range algorithm 2: lower_bound
// ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T const& value)
// ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last,
//                             T const& value, BinaryPredicate op)
// Returns the position of 1st element that has a value equal to
// or greater than value. That is, this is the first position where an element
// with value value could get inserted without breaking the sorting of range [first, last)
// op is an optional binary predicate to be used as the sorting criterion [which
// should be the same as the one used for previously sorting the container].

// Sorted-range algorithm 3: upper_bound
// ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T const& value)
// ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last,
//                             T const& value, BinaryPredicate op)
// Returns the position of 1st element that has a value greater than value.
// That is, this is the first position where an element with value value could
// get inserted without breaking the sorting of range [first, last)
// op is an optional binary predicate to be used as the sorting criterion [which
// should be the same as the one used for previously sorting the container].

// Sorted-range algorithm 4: equal_range
// pair<ForwardIterator,ForwardIterator>
// equal_range(ForwardIterator first, ForwardIterator last, T const& value)
// pair<ForwardIterator,ForwardIterator>
// equal_range(ForwardIterator first, ForwardIterator last, T const& value, BinaryPredicate op)
// Both overloads return the range of elements equal to value. 
// This range comprises the first and the last position an element with value value
// could get inserted without breaking the sorting criterion of range [first, last).
// This is equivalent to: make_pair(lower_bound(...), upper_bound(...))
  
// search where 4 [which doesn't exist] can be inserted in sorted container v2
  print(v2, "v2: ");
  std::vector<int>::const_iterator pos1 = std::lower_bound(std::begin(v2), std::end(v2), -4, myLessAbs{});
  std::vector<int>::const_iterator pos2 = std::upper_bound(std::begin(v2), std::end(v2), -4, myLessAbs{});
// as usual, element positions start at 0 ...
  std::cout << "-4 could get position "
            << std::distance(std::cbegin(v2), pos1)
            << " up to "
            << std::distance(std::cbegin(v2), pos2)
            << " without breaking sorting criterion myLessAbs!!!\n";
// insert -4 at position pos1
  v2.insert(pos1, -4);
  print(v2, "v2: ");

// std::equal_range returns a range specified by the values returned
// by std::lower_bound and std::upper_bound as a pair:
  using VICI = std::vector<int>::const_iterator;
  std::pair<VICI,VICI> pvici = std::equal_range(std::begin(v2), std::end(v2), 6, myLessAbs{});
  // for brevity, I am not checking if pvici contains values equivalent to std::end(vi)!!!
  std::cout << "6 could get position "
          << std::distance(std::cbegin(v2), pvici.first)
          << " up to "
          << std::distance(std::cbegin(v2), pvici.second)
          << " without breaking sorting criterion myLessAbs!!!\n";

// Sorted-range algorithm 5: merge
// OutputIterator
// merge(InputIterator first1, InputIterator last1,
//       InputIterator first2, InputIterator last2,
//       OutputIterator dest)
//
// OutputIterator
// merge(InputIterator first1, InputIterator last1,
//       InputIterator first2, InputIterator last2,
//       OutputIterator dest, BinaryPredicate op)
// Both overloads merge elements of sorted source ranges [first1, last1) and
// [first2, last2) so that destination range starting from dest contains all
// elements that are in the first source range plus those that are in the
// second source range. For example, calling merge for source ranges:
// 5 6 7 8
// 1 2
// gives:
// 1 2 5 6 7 8

  std::vector<int> v3{6, 5, 8, 7};
  std::sort(std::begin(v3), std::end(v3)); // v3 <- 5 6 7 8
  std::set<int> s1{2, 1};                  // s1 <- 1 2

// merge two sorted sequences [both in ascending order]
// into another sequence [also in ascending order]
  std::deque<int> d1;
  std::merge(std::begin(v3), std::end(v3),
             std::begin(s1), std::end(s1),
             std::back_inserter(d1));
// d1 <- 1 2 5 6 7 8
  print(d1, "d1: ");

// now, merge sorted sequences v3 and s1 into d1 using front_inserter
  d1.clear(); // delete all existing elements
  std::merge(std::begin(v3), std::end(v3),
             std::begin(s1), std::end(s1),
             std::front_inserter(d1));
// d1 <- 8 7 6 5 2 1
  print(d1, "d1: ");

// merge two sorted sequences [both in ascending order]
// into another sequence in descending order
  std::set<int, std::greater<int>> s2;
  std::merge(std::begin(v3), std::end(v3),
             std::begin(s1), std::end(s1),
             std::inserter(s2, std::begin(s2)), std::greater<int>{});
  print(s2, "s2: ");
}
