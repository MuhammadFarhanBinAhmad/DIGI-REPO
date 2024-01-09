// CSD2125 11/02
// first example of function object

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

// suppose you want to add a certain value to all container elements
void add10(int& elem) noexcept {
  elem += 10;
}

void f1() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  std::for_each(std::begin(vi), std::end(vi), add10);
  print(vi, "f1: ");
}

// if you need different values that are known at compile time ...
template <int VALUE>
void add(int& elem) noexcept {
  elem += VALUE;
}

typedef void (*PF)(int&);

void f2() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  std::for_each(std::begin(vi), std::end(vi), add<10>);
  print(vi, "f2: ");

  PF pf = add<11>;
  std::for_each(std::begin(vi), std::end(vi), pf);
  print(vi, "f2: ");
}

// function object that adds the value with which it is initialized
class AddValue {
private:
  int value;
public:
  AddValue(int v) : value{v} {}
  int operator()(int& elem) const noexcept { return elem += value; }
};

void f3() {
  std::vector<int> vi{1, 2, 3, 4, 5};
  std::for_each(std::begin(vi), std::end(vi), AddValue(10));
  print(vi, "f3: ");

  std::for_each(std::begin(vi), std::end(vi), AddValue(2));
  print(vi, "f3: ");

  AddValue const rav(10);
  std::for_each(std::begin(vi), std::end(vi), rav); // rav(*iter)
  print(vi, "rav: ");

  int x = 11;
  rav(x);
  std::cout << "x: " << x << "\n";
}

int main() {
  f1();
  f2();
  f3();
}