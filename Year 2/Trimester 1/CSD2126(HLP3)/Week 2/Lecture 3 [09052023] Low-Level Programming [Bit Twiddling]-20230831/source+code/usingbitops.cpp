// HLP3 09/09/2020
// usingbitops.cpp - example usage of bitwise operations

#include <iostream>
#include <cstdint>
#include <string>
#include <array>
#include <cmath>

int main() {
  std::cout << "Enter a number: ";
  uint32_t n;
  std::cin >> n;

  std::cout << "  n = " << n << '\n';
  std::cout << "2*n = " << (n<<1) << '\n';
  std::cout << "4*n = " << (n<<2) << '\n';
  std::cout << "8*n = " << (n<<3) << "\n\n";

  std::cout << "  n = " << n << '\n';
  std::cout << "n*7 = " << ((n<<3) - n) << '\n';
  std::cout << "n*9 = " << ((n<<3) + n) << "\n\n";

  std::cout << "  n = " << n << '\n';
  std::cout << "n/2 = " << (n>>1) << '\n';
  std::cout << "n/4 = " << (n>>2) << '\n';
  std::cout << "n/8 = " << (n>>3) << "\n\n";

  std::cout << "  n = " << n << '\n';
  std::cout << "n%2 = " << (n & ~(~0U << 1)) << '\n';
  std::cout << "n%4 = " << (n & ~(~0U << 2)) << '\n';
  std::cout << "n%8 = " << (n & ~(~0U << 3)) << "\n\n";

  // how many bits are required to store decimal value stored in m?
  uint32_t m = n, lg = 0;
  while (m > 0) {
    m >>= 1; ++lg;
  }
  std::cout << "Number of bits to store decimal value " << n << " is: " << lg << '\n';

  // or we can use standard library math functions to compute the same thing:
  std::cout << "Number of bits to store decimal value " << n << " is: "
            << std::ceil(std::log(static_cast<double>(n))/std::log(2.0)) << '\n';

  // using bitwise operators to pack and unpack data
  std::cout << "Enter pixel value (R,G,B): ";
  uint32_t r, g, b;
  uint8_t c;
  std::cin >> c >> r >> c >> g >> c >> b >> c;
  uint32_t rgb = ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
  std::cout << "COLORREF: " << rgb << std::hex << "(" << rgb << "h)" << "\n\n";

  // bits as space-saving measure
  std::cout << "Enter a pizza code (decimal): ";
  uint32_t code;
  std::cin >> code;
  if ((code & 0xff) == 0) {
    std::cout << "You are ordering a plain pizza" << '\n';
  } else {
    constexpr uint32_t MAX_TOPPINGS{8U};
    std::array<std::string, MAX_TOPPINGS> toppings = {
      "mushroom", "garlic", "pepper", "pepperoni",
      "onion", "sausage", "jalapeno", "pineapple"
    };
    std::cout << "You are ordering a ";
    for (uint32_t i{0U},flag{0x1U}; i < MAX_TOPPINGS; ++i,flag<<=1U) {
      if ((code & flag) != 0U) {
        std::cout << '\"' << toppings[i] << "\" ";
      }
    }
    std::cout << "pizza" << '\n';
  }
}
