// CSD2125: 11/09
// This exam shows how a variety of functions can be stored in polymorphic
// standard library type std::function<>

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <map>

class Button {
public:
  Button(std::function<void(void)> click) : handler{click} {}
  void m_click() const { handler(); }
private:
  std::function<void(void)> handler;
};

std::vector<Button> create_buttons() {
  auto honk = Button([counter = 0] () mutable { 
    std::cout << "HONK HONK " << ++counter << "\n";});
  auto bark = Button([] { std::cout << "beware of dogs\n"; });
  auto mute = Button([]{});
  return std::vector<Button>{honk, bark, mute};
}

int main() {
  std::vector<Button> buttons = create_buttons();
  for (Button const& b : buttons) {
    b.m_click();
  }
  buttons.front().m_click();
}