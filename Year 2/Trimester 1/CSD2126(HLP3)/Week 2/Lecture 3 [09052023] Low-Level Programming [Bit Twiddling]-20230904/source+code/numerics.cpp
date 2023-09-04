// HLP3: 09/09/2020
// Demonstration of queries relating to arithmetic types.
// These queries can be useful in determining the minimum and maximum
// values from a set of values of a specific type. For example, the minimum
// and maximum values would be set to the values returned by max() and
// min() functions, respectively, for the specialization of numeric_limits
// for that type.

#include <iostream>
#include <cstdint>
#include <limits>

int main() {
  // gathering minimum and maximum values stored in fundamental types
  std::cout << "max short: " << std::numeric_limits<int16_t>::max() << "\n";
  std::cout << "max short: " << std::numeric_limits<int16_t>::min() << "\n";
  std::cout << "max double: " << std::numeric_limits<double>::max() << "\n";
  std::cout << "max double: " << std::numeric_limits<double>::min() << "\n";
  std::cout << "max double: " << std::numeric_limits<double>::lowest() << "\n";
}