// HLP2 11/02
// std::for_each is the only algorithm that returns the (updated) function object
// passed to the algorithm.This means that we can use std::for_each algorithm to
// compute things such as averages and other types of summary statistics.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// function template to print contents of containers ...
template <typename Cont>
void print(Cont const& c, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << postfix;
}

class MeanValue {
public:
private:
  int num{}; // number of elements
  int sum{}; // sum of all element values
public:
  void operator() (int elem) noexcept {
    ++num;
    sum += elem;
  }
  double avg() const {
    return static_cast<double>(sum)/static_cast<double>(num);
  }
};

class IncreasingNumberGenerator {
public:
  IncreasingNumberGenerator(int ival) : number{ival} {}
  [[nodiscard]] int operator()() noexcept { return number++; }
private:
  int number {};
};

int main() {
  std::vector<int> vi;
  std::generate_n(std::back_inserter(vi), 5, IncreasingNumberGenerator(10));
  print(vi, "vi: ");

  // find mean value
  MeanValue const m = std::for_each(std::begin(vi), std::end(vi), MeanValue{});
  std::cout << "Average value: " << m.avg() << "\n";
}