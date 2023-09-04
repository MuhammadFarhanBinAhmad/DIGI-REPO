// HLP3: 09/09/2020
// Demonstration of bit-fields as a space-saving tool in C and C++ code
// compile: g++ -std=c++17 -pedantic-errors -Wall -Wextra -Werror bitfields.cpp

#include <iostream>
#include <cstdint>

// Since members one and two will always have values in range [0, 15], bitfields
// can be used bitfields to pack the information into a single byte.
// Accessing the data in these bitfields is the same as with ordinary data members.
struct S {
  using UC = uint8_t;

  UC one : 4; // 0-15
  UC two : 4; // 0-15
};

// structure to store some useful player information ...
struct PlayerAttributes {
  using UC = uint8_t;
  using US = uint16_t;

  UC level;  // stores values 0 - 3
  UC power;  // stores values 0 - 63
  US range;  // stores values 0 - 1023
  UC armor;  // stores values 0 - 15
  US health; // stores values 0 - 511
  UC grade;  // stores values 0 - 1
};

// An object of type PlayerAttributes requires 10 bytes of storage. A slight
// improvement is possible by adjusting the order in which certain members are declared:
struct PlayerAttributes2 {
  using UC = uint8_t;
  using US = uint16_t;

  UC level;  // stores values 0 - 3
  UC power;  // stores values 0 - 63
  UC armor;  // stores values 0 - 15
  UC grade;  // stores values 0 - 1
  US range;  // stores values 0 - 1023
  US health; // stores values 0 - 511
};

// The improved structure definition decreases storage requirements from
// 10 bytes to 8 bytes. Can more be done to further reduce storage requirements?
// One option is to use bit shift operators to pack the data members into
// an uint32_t variable. However, packing and unpacking individual values
// requires a bit of bit-twiddling (see class presentation for packing).
// In some cases, a better option is to use structure bit-fields.
// Accessing such bit-fields is no different than accessing ordinary data
// members with the advantage that the compiler will do the bit-twiddling
// required to pack and unpack the data.
// Here's a bit-field that optimizes the storage of player attributes
// down to 4 bytes:
struct PlayerAttributes3 {
  using UI = uint32_t;

  UI level  : 2;  // stores values 0 - 3
  UI power  : 6;  // stores values 0 - 63
  UI range  : 10;  // stores values 0 - 1023
  UI armor  : 4;  // stores values 0 - 15
  UI health : 9; // stores values 0 - 511
  UI grade  : 1;  // stores values 0 - 1
}; 
// However, a disadvantage of bit-fields is that they may not be consistent
// across machines - endianness, padded bitfields and bytes, implicit type
// conversions to and from bitfields are implementation defined.

int main() {
  // experiments with structure bitfields
  std::cout << "sizeof(S): " << sizeof(S) << '\n';
  S s1;
  s1.one = 0;
  s1.two = 10;
  std::cout << "s1: {" << (int)s1.one << ", " << (int)s1.two << "}\n";

  std::cout << "sizeof(PlayerAttributes) : " << sizeof(PlayerAttributes) << "\n";
  std::cout << "sizeof(PlayerAttributes2): " << sizeof(PlayerAttributes2) << "\n";
  std::cout << "sizeof(PlayerAttributes3): " << sizeof(PlayerAttributes3) << "\n";

  // setting/getting data from bit-fields
  PlayerAttributes3 x{1, 2, 3, 4, 5, 1};
  std::cout << "level: " << x.level << '\n';
  x.armor = x.grade+2;
  std::cout << "armor: " << x.armor << '\n';
}
