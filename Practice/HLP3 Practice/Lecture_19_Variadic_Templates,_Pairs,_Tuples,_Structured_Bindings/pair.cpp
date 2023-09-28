// CSD2125 11/16
// pair.cpp
// The class pair treats two values as a single unit. This class is used
// in several places in the standard C++ library: std::map, std::multimap,
// std::unordered_map, std::unordered_multimap.
// The std::minmax algorithm also returns a pair of smallest and largest
// values.
#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>

// overload operator<<
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& p) {
  return os << "[" << p.first << ", " << p.second << "]";
}

int main() {
  std::pair<std::string, int> psi{"hello", 2};
  std::cout << psi.second << " | " << psi.first << "\n";
  std::cout << psi << "\n";

  // std::minmax returns a std::pair
  std::pair<int, int> pii = std::minmax({1,2,3,4,5,6});
  std::cout << "pii.first: " << pii.first << " | " << pii.second << "\n";

  // each element of std::map is a key-value pair
  std::map<std::string, int> scores;
  scores["tic"] = 11;
  scores.insert(std::make_pair<std::string, int>("tac", 22));
  scores.insert(std::make_pair<std::string, int>("toe", 33));

  for (std::pair<std::string, int> const& p : scores) {
    std::cout << p.first << ": " << p.second << "\n";
  }

  // access each element of pair using index with std::get<index>(pair)
  // or using type with std::get<type>(pair)
  for (std::pair<std::string, int> const& p : scores) {
    std::cout << std::get<std::string>(p) << ": " << std::get<1>(p) << "\n";
  }

  // std::pair is little sibling of std::tuple - so can convert pair to tuple
  // and vice-versa
  std::pair<int, double> pid{1, 1.2};
  std::tuple<int, double> tid = pid;
  std::cout << "[" << std::get<0>(tid) << ", " << std::get<1>(tid) << "]\n";
}