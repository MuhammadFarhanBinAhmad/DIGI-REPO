// HLP2: string-conv.cpp
// 01/24/2022
// Since C++11, the C++ standard library provides convenience functions
// to convert strings into numeric values and to convert numeric values
// to strings.
// For all functions that convert strings to a numeric value, the following
// applies:
// 1) They skip leading whitespace.
// 2) They allow you to return the index of the first character after the
// last processed character.
// 3) They might throw exceptions: std::invalid_argument if no conversion
// is possible and std::out_of_range if the converted value is outside the
// range of representable values for the return type.
//
// The table of numeric conversion functions is shown below:
// ----------------------------------------------------------------------------
// String Function                          |  Effect
// ----------------------------------------------------------------------------
// stoi(str, idx_ret=nullptr, base=10)   | Converts str to an int
// stol(str, idx_ret=nullptr, base=10)   | Converts str to a long
// stoul(str, idx_ret=nullptr, base=10)  | Converts str to an unsigned long
// stoll(str, idx_ret=nullptr, base=10)  | Converts str to a long long
// stoull(str, idx_ret=nullptr, base=10) | Converts str to an unsigned long long
// stof(str, idx_ret=nullptr)            | Converts str to a float
// stod(str, idx_ret=nullptr)            | Converts str to a double
// stold(str, idx_ret=nullptr)           | Converts str to a long double
// ----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <limits>
#include <exception>

int main() {
  try {
    // convert from std::string to numeric type ...
    std::cout << std::stoi("   34") << '\n';
    std::cout << std::stoi("  34.5 ") << '\n';
    std::cout << std::stoi("-0x45") << '\n';
    std::cout << std::stoi("-0x45", nullptr, 16) << '\n';

    // use index of characters not processed
    size_t idx;
    std::cout << std::stoi(" 12 can't handle the truth", &idx);
    std::cout << "idx of first unprocessed char: " << idx << '\n';

    // use octal and hexadecimal bases
    std::cout << std::stoi("111", nullptr, 8)  << '\n';
    std::cout << std::stoi("111", nullptr, 16) << '\n';
    std::cout << std::stoi("789", nullptr, 8)  << '\n';

    // read floating-point values
    std::cout << std::stof("1.2f") << '\n';
    std::cout << std::stod("1.2e5") << '\n';

    // convert numeric value to string
    std::cout << std::to_string(1.2345) << '\n';
    std::cout << std::to_string(-12345) << '\n';

    // get an exception to be thrown ...
    long long ll = std::numeric_limits<long long>::max();
    std::string sll = std::to_string(ll);
    std::cout << std::stoi(sll) << '\n'; // throws an exception
  } catch(std::exception const& e) {
    std::cout << e.what() << '\n';
  }

  // Now that exception has been taken care of, we can continue
  // with normal program ...
}