// CSD2125 11/02
// example of function object that takes two parameters

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

// unary predicate
template <typename T>
class IsAnOddNumber {
public:
  [[nodiscard]] constexpr bool operator()(T value) const noexcept {
    return value%2;
  }
};

// binary predicate
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

  // use predicate to get rid of all odd numbers in container ...
  // the following is C++20 only
  //std::erase_if(numbers, IsAnOddNumber());
  // Pre-C++20 requires use of erase-remove idiom:
  // 1) std::remove is used to move those elements that don't match the removal
  // criteria to the front of the container. The algorithm will return an
  // iterator to the first element of the tail elements of the container.
  // 2) Pass the iterator returned by std::remove and the container's end
  // iterator are then passed to the erase member function of the container ...
  numbers.erase(std::remove_if(std::begin(numbers), std::end(numbers), IsAnOddNumber<int>()), std::end(numbers));
  print(numbers, "numbers : ");

  std::vector<int> numbers2(numbers.size()), numbers3(numbers.size());
  std::generate(std::begin(numbers2), std::end(numbers2), IncreasingNumberGenerator(3));
  print(numbers2, "numbers2: ");
  std::transform(std::begin(numbers), std::end(numbers),
                 std::begin(numbers2), std::begin(numbers3), Add<int>());
  print(numbers3, "numbers3: ");

}
