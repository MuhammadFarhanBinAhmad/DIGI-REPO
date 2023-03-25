// HLP2 11/02
// first example of function object

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

// suppose you want to add a certain value to all container elements
void add10(int& elem) noexcept {
  elem += 10;
}

template<typename FowardIterator,typename UnaryFunction>
UnaryFunction For_Each(FowardIterator first,FowardIterator last, UnaryFunction op)
{
  while (first !- last)

  {
    op(*first);
    ++first;
  }
  return op;
}

// call function add10 repeatedly to increment range of elements ...
void f1() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  std::for_each(std::begin(vi), std::end(vi), add10);
  print(vi, "f1: ");
}

// the disadvantage of function add10 is that it can only increment
// a value by 10 ...
// if you need different values that are known at compile time ...
template <int VALUE>
void add(int& elem) noexcept {
  elem += VALUE;//VALUE ONLY IS KNOW AT RUN TIME
}

// use specific instantiations of function template add to increment
// range of elements as long as the value is known at compile time ...
void f2() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  std::for_each(std::begin(vi), std::end(vi), add<10>);
  print(vi, "f2: ");

  using PF = void (*)(int&);
  PF pf = add<11>;
  std::for_each(std::begin(vi), std::end(vi), pf);
  print(vi, "f2: ");
}

// function object that adds the value with which it is initialized
class AddValue {
private:
  int value; // this is the state of an object of type AddValue
public:
  AddValue(int v) : value{v} {} // set state
  int operator()(int& elem) const noexcept { return elem += value; } // change state
};

// use function objects of type AddValue to to increment range
// of elements with values that don't have to be known at compile time ...
void f3() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  int incrementor{10};
  std::for_each(std::begin(vi), std::end(vi), AddValue(incrementor));//Addvalue paramter value is known at runtime
  print(vi, "f3: ");

  std::for_each(std::begin(vi), std::end(vi), AddValue(2));
  print(vi, "f3: ");

  AddValue const rav(10);
  std::for_each(std::begin(vi), std::end(vi), rav);
  print(vi, "rav: ");

  int x{11};
  rav(x);
  std::cout << "x: " << x << "\n";
}

int main() {
  f1();
  f2();
  f3();
}
