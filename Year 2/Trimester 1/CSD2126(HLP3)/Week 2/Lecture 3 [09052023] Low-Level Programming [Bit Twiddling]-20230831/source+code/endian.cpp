// HLP3 09/09/2020
// How to check if a machine [executing this code] is big- or litte-endian?
// It is a bit of work pre-C++20 but is quite straightfoward since C++20.
// For pre-C++20: g++ -std=c++17 -pedantic-errors -Wall -Wextra -Werror endian.cpp
// For C++20: g++-11 -std=c++20 -pedantic-errors -Wall -Wextra -Werror endian.cpp
#include <iostream>
#include <cstdint>
#if __cplusplus >= 202002L
  #include <bit>      // since C++20
#endif

constexpr bool endian() {
#if __cplusplus >= 202002L // C++20 and beyond
// C++20 makes determing whether machine executing this code
// is big- or little-endian:
	return (std::endian::native == std::endian::big) ? true : false;
#else // pre C++20
// pre-C++20 method for detecting whether machine executing this
// code is big- or little-endian
// function returns true if machine is big-endian; otherwise false.
	constexpr uint32_t val{0x01234567U};
	return (0x67 != *reinterpret_cast<const uint8_t *>(&val)) ? true : false;
#endif
}

int main() {
	std::cout << "you're " << (endian() ? "big" : "little") << "-endian machine\n";
}
