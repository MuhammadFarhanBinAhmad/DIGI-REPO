// HLP3 09/09/2020
// bitset.cpp: using the C++ standard library bitset container
// cs225 10/18

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <bitset>
#include <string>
#include <stdexcept>

int main() {
  std::bitset<16> bs16 = 5;
  std::cout << "a bits: " << bs16 << '\n';
  std::cout << "a base 10 value: " << bs16.to_ulong() << "\n\n";

  std::bitset<10> bs10(std::string("0110001"));
  std::cout << "b bits: " << bs10 << '\n';
  std::cout << "b base 10 value: " << bs10.to_ulong() << "\n\n";
  
  bs16 <<= 4;
  std::cout << std::setw(13) << "a<<4: " << bs16 << '\n';
  bs10 = ((~bs10) >> 2) ^ bs10;
  std::cout << std::setw(13) << "((~b)>>2)^b: " << bs10 << "\n\n";
  
  //bs16 = bs10; // uncomment to see if this statement compiles

  // modifiers ...
  bs16.set(15, true);
  bs16[14] = true;
  bs16.flip(13);

  // iterate thro' counter to count how many bits are set
  uint32_t set = 0;
  for (unsigned i=0; i < bs16.size(); ++i) {
    set += bs16[i] ? 1 : 0;
  }
  std::cout << bs16 << ": " << set << " bits set" << '\n';
  // don't have to iterate - member function count does the work!!!
  std::cout << bs10 << ": " << bs10.count() << " bits set" << "\n\n";

  std::cout << "enter a number: ";
  uint32_t n;
  std::cin >> n;
  std::cout << bs16 << ": bit index " << n;
  try {
    if (!bs16.test(n)) {
      std::cout << " not";
    }
    std::cout << " set" << '\n';
  } catch (std::out_of_range& e) {
    std::cout << " out of range" << '\n';
  }
  std::cout << '\n';

  std::bitset<16>::reference ref = bs16[(n+1)%16U];
  std::cout << bs16 << ": bit " << ((n+1)%16U) << " is " << static_cast<bool>(ref) << '\n';
  ref = false;
  std::cout << bs16 << '\n';
}
