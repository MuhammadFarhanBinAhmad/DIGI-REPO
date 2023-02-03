#include "num.hpp"
#include <iostream>

struct Point {
  double x{}, y{};
};

int main() {
  Num n0;
  std::cout << "n0: " << n0 << '\n';
  n0.set_val(11);
  std::cout << "n0: " << n0 << '\n';
  Num n1{23};
  std::cout << "n1: " << n1 << '\n';

  Num const cn2{123};
  std::cout << "cn2: " << cn2 << '\n';

  Num n2{n1}; // shallow copy implemented thro' a copy ctor
  std::cout << "n2: " << n2 << '\n';

  n2 = n0; // shallow copy implemented thro' a copy assignment
  std::cout << "n2: " << n2 << '\n';

  n2 = 155;
  std::cout << "n2: " << n2 << '\n';

  n0 = n1 + n2; //n0.op=(n1.op+(n2))
  //n0.operator=(n1.operator+(n2));
  std::cout << "n0: " << n0 << '\n';

  n0 += n1;
  n0 += 1;
  n0 = n0 + 1;
  n0 = 2 + n0;
  std::cout << "n0: " << n0 << '\n';

}