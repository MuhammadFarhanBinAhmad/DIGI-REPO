/*
* dist.c - source file containing C code for computing distance between 2 points.
*
* Input from standard input: 4 double values specifying coordinates of 2 points
* Side effect of program: Write to standard output the distance between two
* points whose coordinates are obtained from standard input.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror dist-input.c -o dist-input.out
*
* Run: ./dist-input.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf
#include <math.h>  // contains function prototype of sqrt
double distance(double px, double py, double qx, double qy); // function prototype of distance

int main(void) {
  printf("Enter coordinates of point P: ");
  double px, py;
  scanf("%lf %lf", &px, &py);
  printf("Enter coordinates of point Q: ");
  double qx, qy;
  scanf("%lf %lf", &qx, &qy);
  
  printf("Distance between (%f, %f) and (%f, %f) is %f\n", 
                    px, py, qx, qy, distance(px, py, qx, qy));
  return 0;
}

double distance(double px, double py, double qx, double qy) {
  double w = qx - px;
  double h = qy - py;
  return sqrt(w*w + h*h);
}
