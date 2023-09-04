// CSD2125/CS225: 09/09/2020
// union-color.cpp:
// Packing and unpacking RGBA components becomes simpler through unions.
// Also, provides multiple ways of accessing the color components ...
// Big caveat: You must remove the -pedantic switch because ISO C++
// prohibits anonymous structures ...

#include <iostream>
#include <cstdint>

union Color {
  enum {RED, GREEN, BLUE};
  uint32_t rgbi;
  uint8_t  rgba[4];
  struct {
    uint8_t red, green, blue, pad;
  };

  Color(uint32_t c=0) : rgbi{c} { }
};

int main() {
  Color pixel{0x34567800};
  std::cout << "rgb: (" << static_cast<int>(pixel.rgba[Color::RED]) << ", "
                        << static_cast<int>(pixel.rgba[Color::GREEN]) << ", "
                        << static_cast<int>(pixel.rgba[Color::BLUE]) << ")\n";

  std::cout << "rgb: (" << static_cast<int>(pixel.red) << ", "
                        << static_cast<int>(pixel.green) << ", "
                        << static_cast<int>(pixel.blue) << ")\n";
  std::cout << "sizeof(Color): " << sizeof(Color) << "\n";
}
