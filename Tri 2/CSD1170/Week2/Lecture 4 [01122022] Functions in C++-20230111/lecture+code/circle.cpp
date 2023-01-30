// HLP2: circle.cpp
// 01/18/2022
// The following code contains the definition of function draw_circle
// [that is declared in circle.hpp] and is meant to illustrate the
// idea of extending function parameter lists without changing
// definition of the function.

#include "circle.hpp"

namespace graphics {

/*
Notice that function definitions have nothing to do with default parameter
values if the function declaration is specified in a header file. This is
so because the function definition must implement the algorithm no matter
what the parameter values are.
*/
void draw_circle(int cx, int cy, double radius, Color c) {
  // You can control the minimum number of characters used to print the
  // number by specifying the field width. Leading blanks will be included
  // to fill up the field, but if the number doesn't fit, the extra digits
  // will be printed regardless of the field width. 
  // For neat output of doubles, the fixed format is most useful.
  // In fixed format, the precision specifies the number of digits to the
  // right of the decimal point, and a precision of zero means zero places
  // to the right of the decimal point (i.e. round to the nearest unit).
  std::cout << "(" << std::setw(2) << cx << ", " << std::setw(2) << cy << ") " 
                   << std::fixed << std::setprecision(2) << radius << " ";
  switch(c) {
    case BLACK: std::cout << "Black.\n"; return;
    case BLUE: std::cout  << "Blue.\n"; return;
    case RED: std::cout   << "Red.\n"; return;
    case GREEN: std::cout << "Green.\n"; return;
    default: std::cout    << "Unknown color.\n"; return;
  }
}

} // end namespace graphics
