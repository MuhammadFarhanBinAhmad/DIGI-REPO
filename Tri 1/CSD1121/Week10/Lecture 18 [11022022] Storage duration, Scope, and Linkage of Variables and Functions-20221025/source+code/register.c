/*
register storage class keyword
------------------------------
The register storage class can only be applied to automaic variables
including function parameters. This keyword is used by programmers to request
the compiler that a "hot" (frequently referenced) variable be stored in a CPU
register. The idea is that register variables may result in smaller and faster
programs. However, compilers are free to ignore these requests. The register 
definition looks like this:

regiser int i;
register unsigned char j;

One of the restrictions on register variables is that it is not possible to
take their address regardless of whether the variables are actually placed in
a CPU register or not:

// it is not possible to take the address of a register variable
register long elem_cnt;
long *p = &elem_cnt; // this assignment is in error

The register keyword was popular in the early days of C since compilers were
not good at optimizing code. Since modern compilers can perform sophisticated 
analysis and optimization of code for complex CPU architectures, they can do a 
better job than programmers at allocating registers for individual uses of a 
variable. Therefore, the register keyword is rarely used these days.
*/

#include <stdio.h>

/*
Parameters parr and size and internal variables i and min have automatic
storage duration. All four of these variables come alive when execution
enters function min_val and they die when the function terminates.

Since the array's base address, size, and iterator are frequently referenced,
we request they be given storage in CPU registers so that their runtime 
references can be fast. Since these variables are stored directly in registers,
the code can be smaller because we no longer need to move contents of these
variables between memory and CPU registers. This request is specified using
storage class specifier register in the declaration specifier of variable i.
*/
int min_val(register int const *parr, register int size) {
  int min = parr[0];
  register int i;
  for (i = 1; i < size; ++i) {
    min = (parr[i] < min) ? parr[i] : min;
  }
  return min;
}

int main(void) {
  int grades[] = {20, 5, -5, -20, 11, -30};
  printf("minimum value: %d\n", 
         min_val(grades, sizeof(grades)/sizeof(grades[0])));
  return 0;
}
