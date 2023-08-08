// CSD2125 11/02
// Introduction to the first example of a lambda expression.

#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename Cont>
void print(Cont const& c, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << postfix;
}

// sequence generator ...
class IncreasingNumberGenerator {
public:
  IncreasingNumberGenerator(int ival) : number{ival} {}
  [[nodiscard]] int operator()() noexcept { return number++; }
private:
  int number {};
};

template <typename T>
[[nodiscard]] bool is_odd(T t) {
  return t%2 ? true : false;
}

int main() {
  // say we've have a set of values ...
  std::vector<int> vi;
  std::generate_n(std::back_inserter(vi), 5, IncreasingNumberGenerator(10));
  print(vi, "vi:  ");

  // we'd like to filter collection of odd values from the container ...
  // we can write a function object is_odd ...
  std::list<int> odd;
  std::copy_if(std::begin(vi), std::end(vi),
               std::back_inserter(odd),
               is_odd<int>);
  print(odd, "odd: ");

  std::deque<int> odder;
  std::copy_if(std::begin(vi), std::end(vi),
              std::back_inserter(odder),
              [](int x) { return x%2; });
  print(odder, "odder: ");
}
