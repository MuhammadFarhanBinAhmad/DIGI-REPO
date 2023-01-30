#include <stdio.h>

void swap(double *left, double *right) {
  double hold = *left;
  *left = *right;
  *right = hold;
}

void reverse(double *begin, double *end) {
  --end;
  while (begin < end) {
    swap(begin, end);
    ++begin;
    --end;
  }
}

void print_darr(double const d[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%.2f%c", d[i], i==size-1 ? '\n' : ' ');
  }
}
