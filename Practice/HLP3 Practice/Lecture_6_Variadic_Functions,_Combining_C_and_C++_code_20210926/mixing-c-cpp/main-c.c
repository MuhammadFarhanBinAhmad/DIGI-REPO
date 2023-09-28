// CSD2125
// 09/23/2021
// We wish to import the C++ library declared in drawline.h and
// the C library declared in calc.h
// To import these two libraries into the executable:
// 1) compile only with gcc: gcc -std=c11 <additional flags if you wish> -c main-c.c
// 2) link main-c.o with C++ library drawline.o and C library calc.o:
//    gcc main-c.o calc.o drawline.o -o cland.out
#include <stdio.h>
#include "drawline.h"
#include "calc.h"

int main(void) {
  int x = 10, y = 20;
  printf("%d | %d | %d\n", draw_line(x, y), add(x, y), mul(x, y));
  return 0;
}
