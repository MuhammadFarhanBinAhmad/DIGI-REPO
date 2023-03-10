// HLP2: 03/09/2022
// pair.cpp: Start with concrete classes PairID and NamedInt that encapsulate
// a 2-tuple of types (int, double) and a 2-tuple of types (std::string, int),
// respectively.
// Next, we use the concepts gained from implementing these concrete classes
// to define a class template that uses template type parameters T1 and T2 to
// generically specify the types of the two elements.

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

class PairID {
private:
  int first;
  double second;
public:
  PairID() : first{}, second{} {}
  PairID(int f, double s) : first{f}, second{s} {}

  int First() const { return first; }
  void First(int f) { first = f; }
  double Second() const { return second; }
  void Second(double s) { second = s; }

  void swap(PairID& rhs) { 
    std::swap(first, rhs.first); std::swap(second, rhs.second);}
};

bool operator==(PairID const& lhs, PairID const& rhs) {
  return lhs.First()==rhs.First() && lhs.Second()==rhs.Second();
}

bool operator!=(PairID const& lhs, PairID const& rhs) {
  return !(lhs==rhs);
}

std::ostream& operator<<(std::ostream& os, PairID const& rhs) {
  os << "[" << rhs.First() << ", " << rhs.Second() << "]";
  return os;
}

class NamedInt {
private:
  std::string first;
  int second;
public:
  NamedInt() : first{}, second{} {}
  NamedInt(std::string f, int s) : first{f}, second{s} {}

  // RVO
  std::string const& First() const { return first; }
  void First(std::string const& f) { first = f; }
  int Second() const { return second; }
  void Second(int s) { second = s; }

  void swap(NamedInt& rhs) { 
    std::swap(first, rhs.first); std::swap(second, rhs.second);}
};

bool operator==(NamedInt const& lhs, NamedInt const& rhs) {
  return lhs.First()==rhs.First() && lhs.Second()==rhs.Second();
}

bool operator!=(NamedInt const& lhs, NamedInt const& rhs) {
  return !(lhs==rhs);
}

std::ostream& operator<<(std::ostream& os, NamedInt const& rhs) {
  os << "[" << rhs.First() << ", " << rhs.Second() << "]";
  return os;
}

template <typename T1, class T2>
class Pair {
private:
  T1 first;
  T2 second;
public:
  Pair() : first{}, second{} {}
  Pair(T1 const& f, T2 const& s); // : first{f}, second{s} {}

  T1 const& First() const; // { return first; }
  void First(T1 const& f); // { first = f; }
  T2 const& Second() const; // { return second; }
  void Second(T2 const& s); // { second = s; }

#if 0
  template <typename U, typename V>
  void swap(Pair<U,V>& rhs);
#else
  void swap(Pair&);
#endif
};

#include "pair.tpp"

int main() {
  PairID pid(1,2.1);
  std::cout << "pid: " << pid << "\n";

  NamedInt city_pop("singapore", 5700000);
  std::cout << "city_pop: " << city_pop << "\n";

  Pair<int, double> pid2(1, 2.1);
  //std::cout << "pid2: " << pid2.First() << ", " << pid2.Second() << "\n";

  Pair<short, float> psf1(5, 2.2f);
#if 0
  pid2.swap(psf1);
#endif
  std::cout << "pid2: " << pid2 << "\n";
  std::cout << "psf1: " << psf1 << "\n";

  Pair<std::string, int> high_score("Prasanna Ghali", 1000000);
  //std::cout << "high-score: " << high_score.First() << ", " << high_score.Second() << "\n";
  std::cout << "high score: " << high_score << "\n";

  std::vector vi{1,2,3,4};
  std::cout << "vi: " << vi << "\n";

}
