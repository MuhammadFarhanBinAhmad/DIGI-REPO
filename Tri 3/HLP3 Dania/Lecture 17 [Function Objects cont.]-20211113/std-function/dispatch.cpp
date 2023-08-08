// CSD2125: 11/09
// This exam shows how a variety of functions can be stored in polymorphic
// standard library type std::function<>

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <map>

// function to compute a^b
double power_func(double b, double e) {
  return std::pow(b, e);
}

int main() {
  std::map<char, std::function<double(double, double)>> table;
  table.insert(std::make_pair('+', [](double a, double b) {return a+b;}));
  table.insert(std::make_pair('-', [](double a, double b) {return a-b;}));
  table.insert(std::make_pair('*', [](double a, double b) {return a*b;}));
  table.insert(std::make_pair('/', [](double a, double b) {return a/b;}));
  table.insert(std::make_pair('^', power_func));

  std::cout << "3+5: " << table['+'](3.0, 5.0) << "\n";
  std::cout << "3*5: " << table['*'](3.0, 5.0) << "\n";
  std::cout << "3-5: " << table['-'](3.0, 5.0) << "\n";
  std::cout << "3/5: " << table['/'](3.0, 5.0) << "\n";
  std::cout << "3^5: " << table['^'](3.0, 5.0) << "\n";

  // simple example of C++20 generic lambda (nothing to do with above code) ...
  auto lambda = []<typename T>(std::vector<T> const& v) {
    std::cout << v.length() << "\n";
    return v.empty();
  };
}
