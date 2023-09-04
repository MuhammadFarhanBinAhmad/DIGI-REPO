// CSD2125/CS225 06/02/2022
// init_list.cpp
// -- illustration of facilities provided by C++ standard library
// class template std::initializer_list<T>

#include <iostream>
#include <initializer_list>

std::ostream& operator<<(std::ostream &os, std::initializer_list<int> il) {
  os << '{';
  std::initializer_list<int>::iterator it;
  for (it = il.begin(); it+1 != il.end(); ++it) {
    os << *it << ',';
  }
  os << *it << '}';
  return os;
}

int main() {
  std::initializer_list<int> il = { 1, 2, 3};
  for (std::initializer_list<int>::iterator it = il.begin();  it != il.end(); ++it) {
    std::cout << *it << ' ';

  }
  std::cout << '\n';

  std::initializer_list<int> il2 = { 4, 5, 6, 7};
  for (int i : il2) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::initializer_list<std::initializer_list<int>> il3 = { {1,2}, {3,4}, {5,6} };
  for (std::initializer_list<int> i : il3) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}
