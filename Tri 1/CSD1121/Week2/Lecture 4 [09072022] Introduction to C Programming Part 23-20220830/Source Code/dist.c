/*
* dist.c - source file containing C code for computing distance between 2 points.
*
* Input from standard input: none
* Side effect of program: Write to standard output the 
* distance between (0.0, 0.0) and (3.0, 4.0)
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror dist.c -o dist.out
*
* Run: ./dist.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf
#include <math.h>  // contains function prototype of sqrt
double distance(double px, double py, double qx, double qy); // function prototype of distance

int main(void) {
  double px = 0.0, py = 0.0;
  double qx = 3.0, qy = 4.0;

  printf("Distance between (%f, %f) and (%f, %f) is %f\n", 
                    px, py, qx, qy, distance(px, py, qx, qy));
  return 0;
}

double distance(double px, double py, double qx, double qy) {
  double w = qx - px;
  double h = qy - py;
  return sqrt(w*w + h*h);
}
