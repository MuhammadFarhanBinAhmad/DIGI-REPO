/*
* dayofyear.c - source file motivating the use of arrays to
* aggregate homogeneous data.
*
* Input from standard input: Read two integers representing day of
* month and month in year.
* Side effect of program: Print day of year using two different methods:
* the first based on representing individual months in year using
* separate identifiers and the second based on aggregating months in year
* in array.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror=vla 
*              -Wimplicit-fallthrough -Werror dayofyear.c -o dayofyear.out
*
* Notes: -Wimplicit-fallthrough option is for compiler to ignore
* the potentially unsafe way that the switch statement was written (without
* a break statement).
* -Werror=vla option is for compiler to flag variable length array as error
*
* Run: ./dayofyear.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>
#include <stdbool.h>

// function to compute day of year without using array ...
int day_of_year(int day, int month, int year);
// function to compute day of year using array ...
int day_of_year_array(int day, int month, int year);
// return true for leap year; otherwise false ...
bool is_leap_year(int year);

int main(void) {
  int dom, moy, year; // day-of-month, month-of-year, and year ...

  // basic check for valid input ...
  // will only check if dom is [1, 31] and moy is [1, 12]
  do {
    printf("\nEnter day-of-month and month-of-year and year: ");
    scanf("%d %d %d", &dom, &moy, &year);
  } while (dom < 1 || dom > 31 || moy < 1 || moy > 12 || year < 1);

  // assume valid values for dom and moy ...
  printf("days: %d\n", day_of_year(dom, moy, year));     // without array
  printf("days: %d\n", day_of_year_array(dom, moy, year)); // with array

  return 0;
}

/*
if (year is evenly divisible by 400) OR
              (evenly divisible by 4 AND not evenly divisible by 100)
then year is leap year; otherwise year is not a leap year
*/
bool is_leap_year(int year) {
  return (year%400==0 || (year%4==0 && year%100)) ? true : false;
}

/*
Computing day of year without using array.
Notice that we need have 12 different variables indicating the number
of days in each of the 12 months ...
*/
int day_of_year(int day, int month, int year) {
  int january   = 31, february = 28, march    = 31, april    = 30;
  int may       = 31, june     = 30, july     = 31, august   = 31;
  int september = 30, october  = 31, november = 30;

  int count = 0;
  switch (month) {
    case 12: count += november;
    case 11: count += october;
    case 10: count += september;
    case  9: count += august;
    case  8: count += july;
    case  7: count += june;
    case  6: count += may;
    case  5: count += april;
    case  4: count += march;
    case  3: count += february; count += is_leap_year(year) ? 1 : 0;
    case  2: count += january;
    case  1: count += day;
  }
  return count;
}

int day_of_year_array(int day, int month, int year) {
  int days_in_months[12] = {
    31, 28, 31, 30, // jan, feb, mar, apr
    31, 30, 31, 31, // may, jun, jul, aug
    30, 31, 30, 31  // sep, oct, nov, dec
  };
  int count = day + ((month > 2) ? (is_leap_year(year) ? 1 : 0) : 0);
  for (int m = month-2; m >= 0; --m) {
    count += days_in_months[m];
  }
  return count;
}
