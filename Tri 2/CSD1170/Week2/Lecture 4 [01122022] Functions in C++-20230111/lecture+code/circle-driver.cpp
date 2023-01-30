// HLP2: circle-driver.hpp
// 01/18/2022
// The following code contains the driver that exercises function draw_circle
// [declared in circle.hpp and defined in circle.cpp] and is meant to illustrate
// the idea of extending function parameter lists without clients
// having to refactor their code.

#include <iostream>
#include "circle.hpp"

int main() {
  int x {20}, y {10};
  double rad {20.4};

  // Initially, the developer provided function draw_circle() that draws the
  // circle shape in black color - the function has the following declaration:
  // void draw_circle(int cx, int cy, double radius);
  graphics::draw_circle(x, y, rad);
  graphics::draw_circle(x+2, y-2, rad*0.9);

  // Later, the developer extended the parameter list of draw_circle() in
  // circle.hpp to allow clients to choose the draw color while providing
  // black as the default draw color:
  // void draw_circle(int cx, int cy, double radius, Color c = Color::BLACK);
  // Notice that the default value can only be specified for the right-most parameter.
  graphics::draw_circle(x, y, rad, graphics::Color::RED); // draw color is red
  graphics::draw_circle(x+2, y-2, rad*0.9, graphics::Color::BLUE); // draw color is blue
  graphics::draw_circle(x-4, y+4, rad*1.1); // draw color is the default color black
  graphics::draw_circle(x+2, y-2, rad*0.9, graphics::Color::GREEN); // draw color is blue

  // It was notice that many clients were rendering circles with radius 25.0 units.
  // The developer updated the declaration in circle.hpp to add a new default parameter
  // for the third parameter.
  // Again, notice that radius happens to be the right-most of the
  // parameters that 
  graphics::draw_circle(x, y); // render circles with radius 25 and in black color
  graphics::draw_circle(x, y, 30.0); // render circle with radius 30 and in black color
  graphics::draw_circle(x, y, 35.0, graphics::Color::BLUE); 
}
