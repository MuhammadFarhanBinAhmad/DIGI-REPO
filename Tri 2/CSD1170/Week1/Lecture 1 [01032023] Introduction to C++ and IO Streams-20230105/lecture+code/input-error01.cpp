// HLP2
// 01/12/2022
// Illustrates failed state of istream variable std::cin
// when user enters invalid input on line 11

#include <iostream>

int main() {
  std::cout << "Enter integer value: ";
  int i = -11;
  std::cin >> i; // user enters .75
  std::cout << "i==" << i << "\n";

  std::cout << "Enter fractional value: ";
  double d = 1.1;
  std::cin >> d;
  std::cout << "d==" << d << "\n"; 
}