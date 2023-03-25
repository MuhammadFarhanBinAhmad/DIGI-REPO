// HLP2 11/02
// example of function object that are predicates

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

// predicate
template <typename T>
class IsAnOddNumber {
public:
  [[nodiscard]] constexpr bool operator()(T value) const noexcept {
    return value%2;
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
  print(numbers, "numbers: ");
}
  template <typename FowardIterator,typename UnaryPredicate>
  FowardIterator Remove_If(FowardIterator first, FowardIterator last, UnaryPredicate op)
  {
    while(first != last)
    {
      
    }
  }
