// main.c
#include <stdio.h>

// Declare the external function from the shared library
int add(int a, int b);

int main() {
    int result = add(5, 3);
    printf("Result: %d\n", result);
    return 0;
}