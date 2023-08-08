// CSD2125 11/16
// tuple.cpp
// Tuples represent a heterogeneous list of elements for which the
// types are specified or deduced at compile time.
// The declaration of std::tuple uses variadic templates:
// templace <typename... Types> class tuple;
//
// The tuple interface is straightforward:
// a) You can create a tuple by declaring it either explicitly or implicitly
// with convenience function std::make_tuple()
// b) You can access elements with std::get<>() function template.
// c) You can use std::tie() to create a tuple of references that can be
// used to extract individual values out of a tuple
// d) You can use std::ignore to ignore tuple elements while parsing with std::tie()
#include <iostream>
#include <tuple>
#include <string>
#include <functional>

// printing tuples is a lot of work for you and the compiler
// it uses template metaprogramming to recursively iterate at
// compile time over the elements of a tuple.

// print element with index IDX of tuple with MAX elements ...
template <int IDX, int MAX, typename... Types>
struct print_tuple {
  static void print(std::ostream& os, std::tuple<Types...> const& params) {
    os << std::get<IDX>(params) << (IDX+1==MAX ? "" : ",");
    print_tuple<IDX+1, MAX, Types...>::print(os, params);
  }
};

// partial specialization where the current element IDX and number of
// elements in the tuple MAX are equal, ends the recursion
template <int MAX, typename... Types>
struct print_tuple<MAX, MAX, Types...> {
  static void print(std::ostream& os, std::tuple<Types...> const& params) {
    // empty by design
  }
};

// overload operator<< for tuples
template <typename... Types>
std::ostream& operator<<(std::ostream& os, std::tuple<Types...> const& params) {
  os << "[";
  print_tuple<0, sizeof...(Types), Types...>::print(os, params);
  return os << "]";
}

int main() {
  // create and initialize a heterogeneous three-element tuple:
  std::tuple<std::string, int, float> tup1{"first", 3, 4.17f};

  // with C++17, we can initialize tuple using class template argument deduction
  auto ad = std::tuple{12, 4, 5.17f};

  // alternatively, you can use std::make_tuple() to create a tuple
  // in which the types are automatically derived from initial values
  auto tup2 = std::make_tuple("second", 4, 1.1);

  // passing an index at runtime is not possible:
  // int i{1};
  // std::get<i>(tup1); // error
  std::cout << std::get<0>(tup1) << ", " << std::get<1>(tup1) << ", "
            << std::get<2>(tup1) << "\n"; // first, 3, 4.17
  
  std::cout << std::get<0>(tup2) << ", " << std::get<1>(tup2) << ", "
            << std::get<2>(tup2) << "\n"; // second, 4, 1.1

  // < is lexographical comparison
  std::cout << (tup1 < tup2) << "\n"; // true

  // std::get<0>(tuple) evaluates to reference ...
  std::get<0>(tup2) = "Second";

  std::cout << std::get<0>(tup2) << "," << std::get<1>(tup2) << ","
            << std::get<2>(tup2) << "\n";  // Second, 4, 1.1

  std::cout << (tup1 < tup2) << "\n"; // false

  // can assign pair to tuple and vice-versa
  std::pair<int, bool> ptmp = std::make_pair(1, true);
  std::tuple<int, bool> tup= ptmp;

  // Using references with make_tuple(), you can extract values of a tuple
  // to some other variables:
  std::tuple<int, float, std::string> tifs{77, 9.2f, "tic tac toe"};
  // assign values of tuple to some other variables:
  int i1;
  float f1;
  std::string s1;

  std::make_tuple(std::ref(i1), std::ref(f1), std::ref(s1)) = tifs;
  std::cout << "<" << i1 << ", " << f1 << ", " << s1 << ">\n";

  // std::tie() makes it convenient to create a tuple of references
  std::tuple<int, double, std::string> tids(11, 111.22, "tie");
  int i2;
  float f2;
  std::string s2;
  std::tie(i2, f2, s2) = tids;
  ++i2; ++f2; s2 += " your laces";
  std::cout << "<" << i2 << ", " << f2 << ", " << s2 << ">\n";
  std::cout << "<" << tids << "\n";

  // std::ignore can be used to ignore tuple element(s) while paring with std::tie()
  std::tuple<int, std::string, double> tisd(12, "light shines", 22.22);
  int i3;
  std::string s3;
  double d3;
  std::tie(i3, std::ignore, d3) = tisd;
  std::cout << "<" << ++i3 << ", " << ++d3 << ">\n";
}
