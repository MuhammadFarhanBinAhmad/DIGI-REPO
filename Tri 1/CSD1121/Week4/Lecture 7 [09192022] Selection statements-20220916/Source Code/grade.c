/*
* grade.c - source file containing various functions for computing the 
* letter grade from a number grade that is represented as a 
* floating-point value.
*
* Input from standard input: floating-point number representing a
* letter grade.
* Side effect of program: Compute and write letter grade equivalent of
* user-supplied floating-point grade value.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror grade.c -o grade.out
*
* Run: ./grade.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/

#include <stdio.h>

// function declarations
char letter_grade(double);
char letter_grade_V2(double);
char letter_grade_V3(double);

int main(void) {
  printf("Enter your grade: ");
  double val;
  scanf("%lf", &val);
  printf("Score: %f | letter grade: %c\n", val, letter_grade(val));
  
  val -= 10.0;
  printf("Score: %f | letter grade: %c\n", val, letter_grade_V2(val));
  
  val = 91.0;
  printf("Score: %f | letter grade: %c\n", val, letter_grade_V3(val));
  
  val = 81.0;
  printf("Score: %f | letter grade: %c\n", val, letter_grade_V3(val));
  
  val = 71.0;
  printf("Score: %f | letter grade: %c\n", val, letter_grade_V3(val));
  
  val = 61.0;
  printf("Score: %f | letter grade: %c\n", val, letter_grade_V3(val));
  
  val = 51.0;
  printf("Score: %f | letter grade: %c\n", val, letter_grade_V3(val));
  
  return 0;
}

/* first pass ... */
char letter_grade(double grade) {
  char ltr_grade;
  
  if (grade >= 90.0) {
    ltr_grade = 'A';
  } else {
    if (grade >= 80.0) {
      ltr_grade = 'B';
    } else {
      if (grade >= 70.0) {
        ltr_grade = 'C';
      } else {
        if (grade >= 60.0) {
          ltr_grade = 'D';
        } else {
          ltr_grade = 'F';
        }
      }
    }
  }
  
  return ltr_grade;
}

/*
Second attempt without the syntactic sugercoating of the 1st version.
This is preferred since the else clauses nested inside the outer
else clause line up so that they're easier to read and understad.
*/
char letter_grade_V2(double grade) {
  char ltr_grade;
  
  if (grade >= 90.0) {
    ltr_grade = 'A';
  } else if (grade >= 80.0) {
      ltr_grade = 'B';
  } else if (grade >= 70.0) {
      ltr_grade = 'C';
  } else if (grade >= 60.0) {
      ltr_grade = 'D';
  } else {
    ltr_grade = 'F';
  }
  
  return ltr_grade;
}

/*
Third attempt without using local variable ltr_grade ... 
*/
char letter_grade_V3(double grade) {
  if (grade >= 90.0) {
    return ('A');
  } else if (grade >= 80.0) {
    return ('B');
  } else if (grade >= 70.0) {
    return ('C');
  } else if (grade >= 60.0) {
    return ('D');
  } else {
    return ('F');
  }
}
