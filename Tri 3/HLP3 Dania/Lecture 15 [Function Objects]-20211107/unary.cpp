// CSD2125 11/02
// example of function object that takes one parameter

#include <iostream>
#include <algorithm>
#include <vector>
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

// unary function
class ToSquare {
public:
  [[nodiscard]] constexpr int operator()(int value) const noexcept { 
    return value * value;
  }
};

int main() {
  constexpr std::size_t vec_size {10};
  std::vector<int> numbers(vec_size);
  std::generate(std::begin(numbers), std::end(numbers), IncreasingNumberGenerator(-5));
  std::transform(std::begin(numbers), std::end(numbers), std::begin(numbers), ToSquare{});
  print(numbers, "numbers: ");
}
