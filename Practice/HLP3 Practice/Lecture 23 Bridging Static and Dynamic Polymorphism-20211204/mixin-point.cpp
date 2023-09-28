// CSD2125 11/30
// mixin-point.cpp
// Mixins provide an alternative way to customize the behavior of a
// type without inheriting from it. Mixins essentially invert the
// normal direction of inheritance, because the new classes are "mixed in"
// to the inheritance hierarchy as base classes of a class template rather
// than being created as a new derived class. This approach allows the
// introduction of new data members and other operations without requiring
// any duplication of the interface.
#include <iostream>
#include <vector>
#include <string>

class Color {
public:
  Color() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  ~Color() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
private:
  uint8_t r, g, b, a;
};

class Texture {
public:
  Texture() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  ~Texture() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
private:
  double s, t;
};

template <typename... Mixins>
class Point : public Mixins... {
public:
  Point() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  ~Point() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
private:
  double x, y, z;
};

int main() {
  // we can have zero template parameters to class Point
  Point<> p;
  std::cout << "sizeof(p): " << sizeof(p) << "\n";
std::cout << "-----------------------------------\n";

  // we have one template parameter to class Point
  std::vector<Point<Color>> vpc;
  vpc.emplace_back(Point<Color>{});
  vpc.emplace_back(Point<Color>{});
  for (auto const& x : vpc) {
    std::cout << "x size: " << sizeof(x) << "\n";
  }
std::cout << "-----------------------------------\n";

  // we have two template parameters to class Point
  Point<Color, Texture> pct;
  std::cout << "sizeof(pct): " << sizeof(pct) << "\n";
std::cout << "-----------------------------------\n";
}
