// CSD2125/CS225: 09/14/2020
// union-intro2.cpp: more examples of usage of union types ...

#include <cstdint>
#include <iostream>

// unions are typically used to save space, by not storing all possibilities
// for certain data items that cannot occur together. For example, if we're
// storing zoological information on certain species, our first attempt at
// a data structure might look like this:
struct creature {
  bool    has_backbone;
  bool    has_fur;
  uint8_t num_of_legs_in_excess_of_4;
};

// However, we know that all creatures are either vertebrate or invertebrate.
// We further know that only vertebrate animals have fur, and that only
// invertebrates have more than four legs. Nothing has fur and more than four
// legs, so we can save space by storing these two mutually exclusive fields
// as a union:
union secondary_characteristics {
  bool    has_fur;
  uint8_t num_of_legs_in_excess_of_4;
};
struct creature2 {
  bool                      has_backbone;
  secondary_characteristics form;
};

// here, we use union to specify different interpretations of the same data
union FloatInt {
  float    f;
  uint32_t i;
};

// IEEE 754 format uses 8 bits 23~30 for representing exponent
uint32_t Exponent(FloatInt fi) {
  return (fi.i >> 23) & 0x00ff;
}

// IEEE 754 format uses 23 bits from 0~22 for representing mantissa
uint32_t Mantissa(FloatInt fi) {
  return fi.i & ((1 << 23) - 1);
}

int main() {
  std::cout << "sizeof(creature) : " << sizeof(creature) << "\n";
  std::cout << "sizeof(creature2): " << sizeof(creature2) << "\n";
  creature2 bear{true};
  bear.form.has_fur = true;
  std::cout << "bear "
            << (bear.has_backbone ? "has backbone " : "has no backbone ")
            << (bear.form.has_fur ? "and has fur\n" : "and has no fur\n");

  FloatInt fi{123.456};
  std::cout << "fi has exponent: " << std::hex << "0x" << Exponent(fi) << '\n';
  std::cout << "fi has mantissa: " << std::hex << "0x" << Mantissa(fi) << '\n';
}
