/*
* temp-converter.c - source file illustrating the use of while statement 
* to print a conversion table with 20 rows of temperatures from fahrenheit
* to celsius.
*
* Input from standard input: two floating-point values specifying the
* range of temperatures in fahrenheit.
* Side effect of program: Print table with 20 rows of temperatures from
* fahrenheit to celsius.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror temp-converter.c -o temp-converter.out
*
* Run: ./temp-converter.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>


/*
formula to convert temperature in fahrenheit (f)
to celsius (c): c = 5*(f-32)/9
*/
double fahr_to_celsius(double temp) {
  return 5.0*(temp - 32.0)/9.0;
}

// Macro that can be used as a substitute of above function
#define FAHR_TO_TEMP(x) (5.0*((x)-32.0)/9.0)

int main(void) {
  printf("Enter lower and upper bounds of temperatures: ");
  double lower_bound, upper_bound;
  scanf("%lf %lf", &lower_bound, &upper_bound);
  /*
  We need 20 temperatures in range [lower_bound, upper_bound].
  The step per iteration: (total range of temp)/20.0
                        : (upper_bound - lower_bound)/20.0
  */
  double max_count = 20.0;
  double step = (upper_bound - lower_bound)/max_count;
  double curr_temp = lower_bound; // initializing expression
  while (curr_temp <= upper_bound) { // loop condition
    double celsius_temp = fahr_to_celsius(curr_temp);
    /*
    Print fahrenheit with minimum 3 digits and zero digits after decimal point.
    Print celsius with minimum 6 digits and 1 digit after decimal point.
    */
    printf("%3.0f %6.1f\n", curr_temp, celsius_temp);
    curr_temp += step; // update expression
  }
  
  return 0;
}
