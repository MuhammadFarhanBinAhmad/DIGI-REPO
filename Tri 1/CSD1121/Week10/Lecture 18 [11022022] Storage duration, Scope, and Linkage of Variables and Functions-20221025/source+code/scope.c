#include <stdio.h> // declaration (not definition) of function printf

int x; // declaration (and definition) at file scope: 1

void boo(double x) {  // declaration (and definition): 2
  x = 1.1; // parameter x with function scope "hides" x with file scope
  // printf argument references x with function scope
  printf("boo(double) - value of x: %f\n", x);
}

void coo(void) {
  // interal variable x with function scope hides external
  // variable x with file scope: 3
  short x[2] = {2, 4};
  // printf argument references x with function scope
  printf("coo() - value of x[0]: %hd\n", x[0]);
  if (x[0] > 0) {
    // this x with block scope "hides" all previous declarations: 4
    float x = 3.3f;
    printf("coo() - value of x: %f\n", x);
  } // x from declaration 4 is no longer visible here
  
  // array object from declaration 3 "reappears" and "hides"
  // external variable x
  x[1] = 6;
  printf("coo() - value of x[1]: %hd\n", x[1]);
}

void foo(void) {
  extern int x; // declaration of variable 1 - this declaration is not
                // required since external variable x - defined at file
                // scope - is visible here
  x = 5; // assign value 5 to external variable x
  printf("foo() - value of x: %d\n", x);
}

int main(void) {
  boo(1.2);
  coo();
  foo();
}
