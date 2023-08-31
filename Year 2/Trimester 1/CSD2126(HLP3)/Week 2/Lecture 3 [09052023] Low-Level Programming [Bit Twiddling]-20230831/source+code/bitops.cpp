// HLP3 09/09/2020
// bitops.cpp: manipulating bits using bitwise operators [&, |, ^, ~]

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdint>

/*
The random number generators in Modern C++ provide a lot of flexibility
which is very useful but somewhat overwhelming for beginners. The following
is a set of beginner-friendly functions that are sufficient for many practical
purposes:
*/
#include <random>
namespace {

// std::default_random_engine provides a mathematical formula that allow the
// generation of statistically random values.
std::default_random_engine& global_urng() {
  static std::default_random_engine u{};
  return u;
}

// The random engine will return the next value from a sequence of values.
// But, how will it get its first value? The random device ignites the
// random engine with a seed.
void randomize() {
  static std::random_device rd{};
  global_urng().seed(rd());
}

// we want uniformly distributed int values
uint32_t pick(uint32_t from, uint32_t thru) {
  static std::uniform_int_distribution<uint32_t> d{};
  using param_t = std::uniform_int_distribution<uint32_t>::param_type;
  return d(global_urng(), param_t{from, thru});
}

/*
You only need to remember the following two functions:
a) randomize: make the numbers really random by initializing the generator's seed.
b) pick(uint32_t a, uint32_t b): Give an uint32_t in the interval [a, b] when a and b are uint32_t
*/
}

namespace {
// pretty printing of a integral value as bit string:
std::string GetBits(uint32_t n) {
  const uint32_t mask {0x3};
  std::string str;
	// iterate from least significant position to most significant bit
	// and get bit i's value
  for (uint32_t bit{1}, i{1}; bit != 0; bit <<= 1, ++i) {
    str = (((n & bit) == 0) ? "0" : "1") + str;
		// add space after collection of 4 bits [only if we're not a most significant bit]
    if ((i & mask) == 0 && (bit << 1) > 0) {
      str = " " + str;
    }
  }
  return str;
}
}

int main() {
  randomize();
  std::cout << std::hex;

  uint32_t n = pick(std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
  std::cout << "In hexadecimal: 0x" << n << '\n';
  std::cout << "In binary:      0b" << GetBits(n) << "\n\n";
	
	n = 100;
  std::cout << "In hexadecimal: 0x" << n << '\n';
  std::cout << "In binary:      0b" << GetBits(n) << "\n\n";

  std::cout << "Original:   0b" << GetBits(n) << '\n';
  std::cout << "Left shift: 0b" << GetBits(n<<1) << "\n\n";

  std::cout << "Original:    0b" << GetBits(n) << '\n';
  std::cout << "Right shift: 0b" << GetBits(n>>1) << "\n\n";

  std::cout << "Original:    0b" << GetBits(-n) << '\n';
  std::cout << "Right shift: 0b" << GetBits((-n)>>1) << "\n\n";

  std::cout << " n = 0b" << GetBits(n) << '\n';
  std::cout << "~n = 0b" << GetBits(~n) << "\n\n";

  uint32_t m = pick(std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
  std::cout << "    m = 0b" << GetBits(m) << '\n';
  std::cout << "    n = 0b" << GetBits(n) << '\n';
  std::cout << "m & n = 0b" << GetBits(m&n) << "\n\n";

  std::cout << "    m = 0b" << GetBits(m) << '\n';
  std::cout << "    n = 0b" << GetBits(n) << '\n';
  std::cout << "m | n = 0b" << GetBits(m|n) << "\n\n";

  std::cout << "    m = 0b" << GetBits(m) << '\n';
  std::cout << "    n = 0b" << GetBits(n) << '\n';
  std::cout << "m ^ n = 0b" << GetBits(m^n) << '\n';
}
