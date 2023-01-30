/******************************************************************************
* @filename planets.c
* @author   Prasanna Ghali
* @DP email pghali@digipen.edu 
* @course   High-Level Programming 1
* @date     07/26/2017
* @brief This file contains code that illustrates two concepts: command-line
* parameters and arrays of pointers. The program determines if the unknown
* number of parameters specified by the user are valid planet names.
*
* Usage: ./program.out planet-name1 planet-name2 planet-name3 planet-name4
******************************************************************************/
#include <stdio.h>  // printf
#include <string.h> // strcmp

/*
It is possible for users of a program to send information to the program when
it is first executed. This is done by defining main as a function with two 
parameters which are by convention, referred to as argc and argv.
argc (for "argument count") specifies the number of command-line parameters
including the name of the program.
argv (for "argument vector") is the address of the 1st element of an array 
of char*s. This array of char*s has "argc+1" count of elements.
argc elements ranging from argv[0] through argv[argc-1] are initialized by the
operating system with the addresses of the 1st characters of each of these 
command-line arguments. The last element argv[argc] is initialized with null 
pointer - that is, if you don't know the number of command-line arguments, then
you can continue iterating until you reach the element with null pointer that
is pointing nowhere.

Since a pointer to the 1st element of an array of char* elements will be of 
type char**, we could have declared the 2nd parameter as:
int main(int argc, char **argv) { ... }
*/
int main(int argc, char **argv) {
  enum {NUM_PLANETS = 9};
  char const * planets[NUM_PLANETS] = {
    "Mercury", "Venus",   "Earth",
    "Mars",    "Jupiter", "Saturn",
    "Uranus",  "Neptune", "Pluto"
  };
  for (int i = 1; i < argc; ++i) { // for each command-line parameter
    int j = 0;
    for (; j < NUM_PLANETS; ++j) { // for each planet
      if (strcmp(argv[i], planets[j]) == 0) {
        printf("%s is a planet!!!\n", argv[i]);
        break;
      }
    }
    if (j == NUM_PLANETS) {
      printf("%s is not a planet!!!\n", argv[i]);
    }
  }
  return 0;
}
