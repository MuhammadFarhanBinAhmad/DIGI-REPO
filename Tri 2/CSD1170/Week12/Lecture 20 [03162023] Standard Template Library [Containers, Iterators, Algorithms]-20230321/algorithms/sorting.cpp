// HLP2 04/01/2022
// sorting.cpp
// STL provides several algorithms to sort elements of a range. In addition to
// full sorting [provided by std::sort and std::stable_sort], STL provides
// variants of partial sorting [provided by std::partial_sort, partial_sort_copy],
// sorting according to the nth element [provided by nth_element], heap algorithms
// [provided by make_heap, push_heap, pop_heap, sort_heap].
// We'll only be considering full sorting algorithms: std::sort and std::stable_sort.
//
// NOTE: Because std::list, std::forward_list, and associative containers provide
// no random-access iterators, you can't use these containers as a destination
// for sorting algorithms. This is not a problem since associative containers
// have elements sorted automatically. std::list and std::forward_list provide a
// special member function to sort.

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <functional>
#include <cmath>

namespace { // start anonymous namespace ...

struct Point {
  double x{}, y{};
  Point(double dx=0., double dy=0.) : x{dx}, y{dy} {}
  double dist() const { return std::sqrt(x*x+y*y); }
  double dist2() const { return x*x+y*y; }
  double const& X() const { return x; }
  double&       X()       { return x; }
  double const& Y() const { return y; }
  double&       Y()       { return y; }
  double operator()() const { return dist(); }
};

bool operator<(Point const& lhs, Point const& rhs) {
  return lhs.dist2() < rhs.dist2();
}

bool operator>(Point const& lhs, Point const& rhs) {
  return rhs.dist2() < lhs.dist2();
}

std::ostream& operator<<(std::ostream& os, Point const& rhs) {
  os << "(" << rhs.X() << ", " << rhs.Y() << ")/" << rhs.dist() << " ";
  return os;
}

// binary predicate to compare two strings based on their length
bool less_length(std::string const& lhs, std::string const& rhs) {
  return lhs.length() < rhs.length();
}

template <typename Cont>
void print(Cont const& coll, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << postfix;
}

} // end anonymous namespace

int main() {
// Sorting all elements algorithm 1a: sort
// void sort(RandomAccessIterator first, RandomAccessIterator last)
// Sort all elements in the range [first, last) with operator< [ascending order]
// sort guarantees a good performance (n-log-n) on average.

  std::vector<Point> v1{{0.6, 4.1}, {-2, 1.9}, {1.1, -1.1}, {0, 2.1}, {-1, 2.2}};
// sort points [based on their distance from origin] in ascending order ...
  std::sort(std::begin(v1), std::end(v1));
  print(v1, "v1: ");

// Sorting all elements algorithm 1a: sort
// void sort(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate)
// Sort all elements in range [first, last) using binary predicate op(elem1, elem2)
  std::vector<Point> v2{{0.6, 4.1}, {-2, 1.9}, {1.1, -1.1}, {0, 2.1}, {-1, 2.2}};
// sort points [based on their distance from origin] in descending order ...
  std::sort(std::begin(v2), std::end(v2), std::greater<Point>{});
  print(v2, "v2: ");

// Sorting all elements algorithm 2a: stable_sort
// void stable_sort(RandomAccessIterator first, RandomAccessIterator last);
// Sorting all elements algorithm 2a: stable_sort
// void stable_sort(RandomAccessIterator first, RandomAccessIterator last,
//                 BinaryPredicate op);
// stable_sort is similar to sort except that stable_sort guarantees that 
// elements that compare as equal retain their original relative positions.

// fill two collections with same elements
  std::vector<std::string> vs {
    "1xxx", "2x", "3x", "4x", "5xx", "6xxxx",
    "7xx", "8xxx", "9xx", "10xxx", "11", "12",
    "13", "14xx", "15", "16", "17"
  };
  std::deque<std::string> ds{std::begin(vs), std::end(vs)};
  print(vs, "vs: ");

// sort [according to the length of strings]
  std::sort(std::begin(vs), std::end(vs), less_length);
  std::stable_sort(std::begin(ds), std::end(ds), less_length);
  print(vs, "vs: ");
// notice that stable_sort preserves relative order of elements ...
  print(ds, "ds: ");
}
