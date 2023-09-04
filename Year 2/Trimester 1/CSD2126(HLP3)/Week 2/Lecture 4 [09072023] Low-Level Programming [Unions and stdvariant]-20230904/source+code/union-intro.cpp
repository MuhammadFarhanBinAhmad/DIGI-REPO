// CSD2125/CS225: 05/14/2018
// union-intro.cpp - basic examples of usage of union types ...

#include <iostream>
#include <iomanip>

union ShortBytes {
  short as_short;
  char as_chars[2];
  struct { unsigned char lsb, msb; } as_bytes;
};

union Vector2D {
  float array[2];
  struct { float x, y; } element;
};
  
int main() {
  ShortBytes sb;
  sb.as_chars[0] = 'N'; sb.as_chars[1] = 'O';
  std::cout << "in decimal: " << sb.as_short << std::endl;
  std::cout << std::hex;
  std::cout << "in hex: " << sb.as_short << std::endl;
  std::cout << "as string: " << sb.as_bytes.lsb << sb.as_bytes.msb << std::endl;
  std::cout << "low byte: " << int(sb.as_bytes.lsb) << std::endl;
  std::cout << "high byte: " << int(sb.as_bytes.msb) << std::endl;
  std::cout << std::dec;
  std::cout << "size: " << sizeof(sb) << std::endl;
  std::cout << std::endl;

  Vector2D v;
  v.array[0] = 1.2f;
  v.array[1] = 3.4f;
  std::cout << "v: " << '(' << v.element.x << ',' << v.element.y << ')' << std::endl;
  std::cout << "size: " << sizeof(v) << std::endl;
}

