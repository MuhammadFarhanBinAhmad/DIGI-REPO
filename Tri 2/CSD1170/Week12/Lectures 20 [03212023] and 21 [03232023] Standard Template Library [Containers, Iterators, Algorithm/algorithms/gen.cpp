// HLP2 11/02
// example of function object that takes zero parameters

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
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

// nodiscard is a C++17 attribute that will make compiler issue a warning
// if the return value of function is not used ...
// Example of a class whose instantiations behave as generators ...
class IncreasingNumberGenerator {
public:
  IncreasingNumberGenerator(int ival) : number{ival} {}
  // this member function is called generator because it spits out a
  // value without requiring any input parameters ...
  [[nodiscard]] int operator()() noexcept { return number++; }
private:
  int number{};
};

template <typename OutputIterator,typename UnaryFunction>
OutputIterator Generate(OutputIterator first,OutputIterator last,UnaryFunction op)
{
  while(first != last)
  {
    *first = op();
    ++first;
  }
  return first;
}

int main() {
  constexpr std::size_t vec_size {10};
  IncreasingNumberGenerator ing{5};
  for (size_t i{}; i < vec_size; ++i) {
    std::cout << "i: " << i << " | ing(): " << ing() << "\n";
  }

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
