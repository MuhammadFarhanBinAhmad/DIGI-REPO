/*
Static variables may be internal (i.e., local) to a block or external to all
blocks, but in either case, remain in existence permanently throughout program
execution, rather than appearing and disappearing as functions are called and 
exited. Therefore, they retain their values even after the functions that have
changed their values return.

Variables declared outside all blocks and functions are called external variables
and they always have static storage. In the following code fragment, variables
students_count and highest_grade are external variables and are therefore alive
throughout the execution of the program.
*/

#include <stdio.h> // declare function printf
/*
Since the two variables below are defined external to all functions, they've 
static storage duration and they'll be alive throughout the program's duration.
Since definition for variable highest_grade doesn't have an initializer, it is
initialized at program startup with value 0.
*/
int students_count = 5;
int highest_grade; // will be initialized with value 0

// declaration (not definition) of function max_val
void max_val(int const arr[], int elem_cnt);

// declaration (and definition) of function main
int main(void) {
  // variable grades has automatic storage duration
  int grades[] = {20, 70, 40, 60, 30};
  
  // assign return value from function max_val that is defined
  // somewhere else to external variable highest_grade
  max_val(grades, students_count);
  printf("highest grade is: %d\n", highest_grade);
}

// declaration (and definition) of function max_val where parameters
// arr, size and variables i and max have automatic storage duration
void max_val(int const arr[], int size) {
  highest_grade = arr[0];
  for (int i = 1; i < size; ++i) {
    highest_grade = (arr[i] > highest_grade) ? arr[i] : highest_grade;
  }
}
