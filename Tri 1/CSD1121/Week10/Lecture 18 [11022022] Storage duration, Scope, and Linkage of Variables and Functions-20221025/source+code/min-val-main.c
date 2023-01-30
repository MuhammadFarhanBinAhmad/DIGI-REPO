#include <stdio.h>

// minval is external variable
// by default, initialized to zero
// by default, name minval can be referenced by
// functions in other source files
int minval;
extern void min_val(int const *, int);

int main(void) {
  int grades[] = {20, 5, -5, -20, 11, -30};
  min_val(grades, sizeof(grades)/sizeof(grades[0]));
  printf("minimum value: %d\n", minval);
  return 0;
}
