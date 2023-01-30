/*
* temp-converter-for.c - source file illustrating the use of for statement
* to print a table of 20 rows with each row containing temperatures in 
* Fahreheit and Celsius.
*
* Input from standard input: Range of temperatures to convert in Fahrehheit
* Side effect of program: Print table with 20 rows of temperatures in
* Fahrenheit and corresponding temperatures in Celsius.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror temp-converter-for.c -o temp-converter-for.out
*
* Run: ./temp-converter-for.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>
/*
Program to print conversion table of temperatures from
fahrenheit to celsius using a for loop.
The table should have no more than 20 rows.
*/

/*
formula to convert temperature in fahrenheit (f)
to celsius (c):
c = 5*(f-32)/9
*/
double fahr_to_celsius(double temp) {
  return 5.0*(temp - 32.0)/9.0;
}

// Macro that can be used as a substitute of above function
#define FAHR_TO_TEMP(x) (5.0*((x)-32.0)/9.0)

int main(void) {
  printf("Enter range of temperatures to convert from Fahrenheit: ");
  double lower_bound, upper_bound;
  scanf("%lf %lf", &lower_bound, &upper_bound);
  
  // what is the step per iteration: (total range of temp)/20
  int max_count = 20;
  double step = (upper_bound - lower_bound)/max_count;
  
  /*
  general form of the for loop:
  for (initializing expression; loop condition; update expression)
    statement
  */
  for (double temp = lower_bound; temp <= upper_bound; temp += step) {
    float celsius_temp = FAHR_TO_TEMP(temp);
    printf("%3.0f\t%6.1f\n", temp, celsius_temp);
  }
  
  return 0;
}
