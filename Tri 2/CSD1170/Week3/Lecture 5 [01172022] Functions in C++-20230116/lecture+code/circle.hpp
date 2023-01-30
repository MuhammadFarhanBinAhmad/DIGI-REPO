// HLP2: circle.hpp
// 01/18/2022
// The following code contains the declaration of function draw_circle
// and is meant to illustrate the idea of extending function parameter
// lists without changing definition of the function.

#include <iostream>
#include <iomanip> // std::setw, std::fixed, std::setprecision

namespace graphics {

// simulate color using integer values
enum Color { BLACK, BLUE, RED, GREEN };

// this was the declaration when the project began ...
#if 0
void draw_circle(int cx, int cy, double radius);
#endif

// At a later point of time, the developer realizes that clients seem to
// mostly draw BLACK circles. To make the function be more convenient for
// clients, the developer adds a default value for this parameter
// There are two nice things going on:
// 1) The developer doesn't need to update the definition of this function!!!
// 2) Clients can continue to use the function both the old way (by providing
// three parameters: cx, cy, and radius) or the new way (by providing
// four parameters: cx, cy, radius, and Color).
#if 0
void draw_circle(int cx, int cy, double radius, Color c = Color::BLACK);
#endif

// This is the current status ...
// In addition to providing clients a default value for the COLOR parameter,
// the developer has extended the function to take a default value of 25.0
// for parameter radius.
// Again, the nice thing is that the developer doesn't need to update the
// definition of this function.
void draw_circle(int cx, int cy, double radius = 25.0, Color c = Color::BLACK);

} // end namespace graphics
