/*
Automatic variables are local or internal to a code block - they come alive
when program execution enters the block and disappear when program execution
exits the block. By default, all variables defined in a function or a block
have automatic storage duration. The same is true for the parameters of a
function which are in effect local variables.

Because automatic variables come and go with function invocation, they don't
retain their values from one call to the next, and must be explicitly 
initialized upon each entry (to the function). If they are not set, they will
contain unknown values left behind by previous occupant(s) of the memory storage.

auto storage class
------------------
All automatic variables can be declared by adding keyword auto to the variable's
declaration specifier. Keyword auto is almost never explicitly specified, since
it is the default for automatic variables. In other words, auto is irrelevant
when declaring variables inside functions, since you get it by default.
*/

#include <stdio.h> // declare function printf

int main(void) {
  // since grades is defined inside a function,
  // it will by default have automatic storage.
  auto int grades[] = {20, 70, 40, 60, 30};
  
  // count will by default have automatic storage whether
  // keyword auto is specified or not
  auto int count = sizeof(grades)/sizeof(grades[0]);
  printf("Number of students: %d\n", count);

  // this is a block inside function block main
  {
    // variable i will also have automatic storage duration and will
    // come alive when program execution enters this block
    auto int i;
    printf("Array elements are: ");
    for (i = 0; i < count; ++i) {
      printf("%i%s", grades[i], (i == count-1) ? "\n" : " ");
    } // variable i disappears when program execution exits block
  }
  
  return 0;
}
