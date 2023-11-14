// CSD2125/CS225 10/26
// class-var-temp.cpp
// This example illustrates the use of parameter packs in class templates
// which obeys the following typical pattern:
// 1) Perform an operation on the first element of the parameter pack and
// recursively invoke the operation on the remaining elements.
// 2) The recursion ends after a finite number of steps.
// 3) The boundary condition is a fully specialized template.

#include <iostream>

// class template Mult takes template arguments of type int
// and returns their product ...
// as you will see, the primary class template Mult is never
// used and therefore only declared but not defined ...
template <int...>
struct Mult;

// full specialization of class template Mult when there are
// zero template arguments
template <>
struct Mult<> {
  static int const value {1};
};

// partial specialization of class template Mult
template <int i, int... tail>
struct Mult<i, tail...> {
  static int const value = i * Mult<tail...>::value;
};

int main() {
  std::cout << "Mult<>::value:          " << Mult<>::value << std::endl;
  std::cout << "Mult<10>::value:        " << Mult<10>::value << std::endl;
  std::cout << "Mult<-1>::value:        " << Mult<-1>::value << std::endl;
  std::cout << "Mult<10,10,10>::value:  " << Mult<10,10,10>::value << std::endl;
  std::cout << "Mult<1,2,3,4,5>::value: " << Mult<1,2,3,4,5>::value << std::endl;
}

