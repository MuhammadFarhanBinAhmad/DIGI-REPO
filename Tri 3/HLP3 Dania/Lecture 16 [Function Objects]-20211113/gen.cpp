// CSD2125 11/02
// example of function object that takes zero parameters

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <string>

template <typename Cont>
void print(Cont const& c, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << postfix;
}

class IncreasingNumberGenerator {
public:
  IncreasingNumberGenerator(int ival) : number{ival} {}
  [[nodiscard]] int operator()() noexcept { return number++; }
private:
  int number {};
};

int main() {
  constexpr std::size_t vec_size {10};
  std::vector<int> numbers(vec_size);
  std::generate(std::begin(numbers), std::end(numbers), IncreasingNumberGenerator(5));
  print(numbers, "numbers: ");

  std::list<int> li;
  std::generate_n(std::back_inserter(li), 9, IncreasingNumberGenerator(9));
  print(li, "li: ");

  // replace second to last element but one with values starting at 42
  std::generate(std::next(li.begin()), std::prev(li.end()), IncreasingNumberGenerator(42));
  print(li, "li: ");
}
