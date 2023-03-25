// HLP2 11/02
// example of function object that takes two parameters

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// function template to print contents of containers ...
template <typename Cont>
void print(Cont const& c, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << postfix;
}

// Example of a class whose instantiations behave as generators ...
class IncreasingNumberGenerator {
public:
  IncreasingNumberGenerator(int ival) : number{ival} {}
  [[nodiscard]] int operator()() noexcept { return number++; }
private:
  int number{};
};

// unary function object
class ToSquare {
public:
  [[nodiscard]] constexpr int operator()(int value) const noexcept { 
    return value * value;
  }
};

// binary function object
template <typename T>
class Add {
public:
  [[nodiscard]] T operator()(T const& lhs, T const& rhs) const noexcept {
    return lhs + rhs;
  }
};

int main() {
  constexpr std::size_t vec_size {10};
  std::vector<int> numbers(vec_size);
  std::generate(std::begin(numbers), std::end(numbers), IncreasingNumberGenerator(-2));
  std::transform(std::begin(numbers), std::end(numbers), std::begin(numbers), ToSquare());
  print(numbers, "numbers: ");

  std::vector<int> numbers2(numbers.size()), numbers3(numbers.size());
  std::generate(std::begin(numbers2), std::end(numbers2), IncreasingNumberGenerator(3));
  print(numbers2, "numbers2: ");
  // use of binary function object ...
  std::transform(std::begin(numbers), std::end(numbers),
                 std::begin(numbers2), std::begin(numbers3), Add<int>());
  print(numbers3, "numbers3: ");

}
