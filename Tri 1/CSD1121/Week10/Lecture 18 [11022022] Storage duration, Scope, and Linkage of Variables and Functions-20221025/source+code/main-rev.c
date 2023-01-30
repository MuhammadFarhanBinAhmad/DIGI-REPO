#include <stdio.h>
void reverse(double*, double*);
void print_darr(double const[], int);

/*
The author of this program has no knowledge of a swap function
in the implementation of function reverse (in rev.c).
Because function - by default - have external linkage, the object
files will not link into an executable.
Moral: authors of functions must - by default - make these functions
have internal linkage by using keyword static.
*/
void swap(int *left, int *right) {
  int hold = *left;
  *left = *right;
  *right = hold;
}


int main(void) {
  double grades[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
  int size = sizeof(grades)/sizeof(grades[0]);
  reverse(grades, grades+size);
  printf("grades: "); print_darr(grades, size);

  int x = 10, y = 20;
  swap(&x, &y);
  printf("x: %d | y: %d\n", x, y);

  return 0;
}
