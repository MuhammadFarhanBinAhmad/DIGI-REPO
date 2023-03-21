/*
A set is a sorted container in which each element can appear at most once.
Adding a second element equal to any of the elements already in the set
has no effect.
By default, operator < is used to sort elements.
The entries in the set are internally stored in a tree so that they
can be accessed with logarithmic complexity.
A set container is used to quickly determine whether it contains a
given value or not. It is often used to create or manage a collection
of duplicate-free elements.
*/
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>

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
  // the following is a collection of int values stored in ascending
  // order with no duplicates:
  std::set<int> si {4, 1, 9, 7, 4, 3};
  print(si, "si: ");
  
  // add more values - notice that elements are stored in terms
  // of their value
  si.insert({4, 3, 5, 1, 6, 2});
  print(si, "si: ");

  // value 5 already exists - insert again and check its return status
  std::pair<std::set<int>::iterator, bool> status = si.insert(5);
  if (status.second == false) {
    std::cout << "5 already exists - was not inserted!!!\n";
  }

  // The presence of a value in a set can be tested by member functions find and
  // count. find returns an iterator referring to the value or if not found to the
  // end iterator. 
  std::set<int>::iterator sit = si.find(9);
  if (sit == std::end(si)) {
    std::cout << "9 doesn't exist in set si!!!\n";
  }

  // If we don't need the iterator, count is more convenient. Note that since
  // duplicates are not allowed, the count value in a set can be either 0 or 1:
  std::set<int>::size_type ct = si.count(8);
  if (ct == 0) {
    std::cout << "8 doesn't exist in set si!!!\n";
  } else {
    std::cout << "8 exists in set si!!!\n";
  }

  // assign elements in si to another set in descending order ...
  std::set<int, std::greater<int>> si2(std::begin(si), std::end(si));
  print(si2, "si2: ");

  // remove all elements of si2 upto element with value 3 ...
  si2.erase(std::begin(si2), si2.find(3));
  print(si2, "si2: ");

  // copy elements of si2 to vector<int>:
  std::vector<int> vi(std::begin(si2), std::end(si2));
  print(vi, "vi: ");

  // copy elements of vi to a multiset:
  std::multiset<int> mi(std::begin(vi), std::end(vi));
  // add element 9 twice ...
  mi.insert(9);
  mi.insert(9);
  print(mi, "mi: ");
  // print the number of times value 9 exists in mi:
  std::cout << "9 exists " << mi.count(9) << " times in mi!!!\n";
}
