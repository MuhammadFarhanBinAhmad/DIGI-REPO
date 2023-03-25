// HLP2 04/01/2022
// removing.cpp
// Removing algorithms remove elements from a range according to their value or
// to a criterion. These algorithms, however, cannot change the number of
// elements.
// The algorithms move logically only by overwriting "removed" elements with the
// following elements that were not removed. They return the new logical end of
// the range [the position after the last element not removed].
// We will look at three kinds of removing algorithms:
// 1) Removing certain values in a sequence [std::remove, std::remove_if]
// 2) Removing certain values in a sequence while copying [std::remove_copy,
//    remove_copy_if]
// 3) Removing consecutive duplicates [std::unique]
// 4) Removing consecutive duplicates while copying [unique_copy]
//
// NOTE: These algorithms cannot be used for associative containers because
// changing the value or position of elements violates the order maintained
// by the container.

#include <iostream>
#include <string>
#include <vector>
#include <deque>
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
class LessThan {
public:
  LessThan(T const& v) : val{v} {}
  bool operator()(T const& v) const { return v < val; }
private:
  T val;
};

} // end anonymous namespace ...

int main() {
// Reversing certain elements in a sequence algorithm 1a: remove
// ForwardIterator
// remove(ForwardIterator first, ForwardIterator last, T const& value)
// Removes each element in range [first, last) that is equal to value
// The algorithm overwrites "removed" elements by the following elements
// that were not removed.
// The algorithm returns the logical new end of the modified sequences [the
// position after the last element not removed]
// The order of elements that were not removed remains stable.
// It is up to the caller to use the returned new logical end instead of
// the value returned by std::end(container).

// fill container with lots of values and make copies:
  std::vector<int> v1;
  insert_elements(v1, 2, 6);
  insert_elements(v1, 4, 9);
  insert_elements(v1, 1, 7);
  std::vector<int> v2{v1}, v3{v1};
  print(v1, "v1: ");

// the following illustrates the remove-erase idiom:
// remove all elements with value 5
  std::vector<int>::iterator vit = std::remove(std::begin(v1), std::end(v1), 5);
  print(v1, "v1: ");
// notice that the container's size has not changed ...
// erase the "removed" elements in the container ...
  v1.erase(vit, std::end(v1));
  print(v1, "v1: ");

// the same as above [remove all elements with value 4]
  v1.erase(std::remove(std::begin(v1), std::end(v1), 4), std::end(v1));
  print(v1, "v1: ");

// Reversing certain elements in a sequence algorithm 1b: remove_if
// ForwardIterator
// remove(ForwardIterator first, ForwardIterator last, UnaryPredicate op)
// Removes each element in range [first, last) for which op(elem) is true.
// Everything else is similar to std::remove
  
  print(v2, "v2: ");
// remove all elements with value less than 4
  v2.erase(std::remove_if(std::begin(v2), std::end(v2), LessThan<int>{4}), std::end(v2));
  print(v2, "v2: ");

// Reversing certain elements in a sequence while copying algorithm 2a: remove_copy
// OutputIterator
// remove_copy(InputIterator first, InputIterator last,
//             OutputIterator dest, T const& value)
// Combination of std::copy and std::remove
// Copies each element in source range [first, last) that is not equal to value
// into the destination range starting with dest.
// The algorithm returns the position after the last copied element in the
// destination range [the first element that is not overwritten].
// The caller must ensure that destination range is big enough or that insert
// iterators are used.
  std::list<int> d1;
  std::remove_copy(std::begin(v2), std::end(v2), std::back_inserter(d1), 6);
  print(v2, "v2: ");
  print(d1, "d1: ");

// Reversing certain elements in a sequence while copying algorithm 2b: remove_copy_if
// OutputIterator
// remove_copy_if(InputIterator first, InputIterator last,
//             OutputIterator dest, UnaryPredicate op)
// Combination of std::copy and std::remove_if
// Copies each element in source range [first, last) for which unary predicate
// op(elem) yields false into the destination range starting at dest

// remove all elements in d1 less than 5
  std::deque<int> d2;
  std::remove_copy_if(std::begin(d1), std::end(d1), std::back_inserter(d2), LessThan<int>{5});
  print(d2, "d2: ");

// Removing consecutive duplicates algorithm 3: std::unique
// ForwardIterator unique(ForwardIterator first, ForwardIterator last)
// Collapses consecutive equal elements by removing the following duplicates.
// The algorithm will remove all elements that are equal to the previous elements.
// Thus, only when the elements in the sequence are sorted, or at least when all
// elements of the same value are adjacent, does it remove all duplicates.
// The algorithm overwrites "removed" elements by the following elements that
// were not removed.
// The algorithm returns the logical new end of the modified sequence [the position
// after the last element not removed]

// d2 has equivalent consecutive elements - so we won't sort the container:
  d2.erase(std::unique(std::begin(d2), std::end(d2)), std::end(d2));
  print(d2, "d2: ");

// Removing consecutive duplicates while copying algorithm 4: std::unique_copy
// OutputIterator unique_copy(InputIterator first, InputIterator last,
//                            OutputIterator dest)
// Combination of std::copy and std::unique
// Copies all elements of source range [first, last) that are not duplicates
// of their previous elements into the destination range starting with dest

// sort v3
  std::sort(std::begin(v3), std::end(v3));
  print(v3, "v3: ");
// copy unique elements into v4
  std::vector<int> v4;
  std::unique_copy(std::begin(v3), std::end(v3), std::back_inserter(v4));
  print(v4, "v4: ");
}
