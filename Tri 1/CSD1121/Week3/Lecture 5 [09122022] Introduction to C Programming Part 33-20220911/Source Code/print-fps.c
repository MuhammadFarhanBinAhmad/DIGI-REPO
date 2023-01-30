/*
* print-ints.c - shows format specifiers (f or F, e or E, g or G) and length
* modifiers (L) used by function printf for printing floating-point values.
*
* Input (from standard input): none
* Side effect of program: Write to standard output various floating-point
* values illustrating format specifiers of printf function
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror print-fps.c -o print-fps.out
*
* Run: ./print-fps.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h> // contains function prototype of printf

int main(void) {
  double d  = 1234567.89;
  double d2 = 0.0000875;
  float f  = d;
  float f2 = d2;

  /*
  Format specifiers f, e, E display values with six digits of precision to the
  right of the decimal point by default (e.g., 1.234567).
  Format specifier f always prints at least one digit to the left of the
  decimal point.
  Format specifiers e/E print e/E, respectively, preceding the exponent, and
  print exactly one digit to the left of the decimal point.
  */
  
  // format specifier f to print float
  printf("Print float  using format specifier %%f: %f\n", f); 
  // format specifier f to print double
  printf("Print double using format specifier %%f: %f\n", d);
  // format specifier F to print float
  printf("Print float  using format specifier %%F: %F\n", f);
  // format specifier F to print double
  printf("Print double using format specifier %%F: %F\n", d);
  // format specifier e to print float
  printf("Print float  using format specifier %%e: %e\n", f);
  // format specifier e to print double
  printf("Print double using format specifier %%e: %e\n", d);
  // format specifier E to print float
  printf("Print float  using format specifier %%E: %E\n", f);
  // format specifier E to print double
  printf("Print double using format specifier %%E: %E\n", d);

  /*
  Format specifier g/G prints in either e/E or f/F format with no trailing 
  zeros (1.234000 is printed as 1.234).
  Values are printed with e/E if, after conversion to exponential notation, the
  value's exponent is less than -4, or the exponent is greater than or equal to
  the specified precision (six significant digits by default for g/G).
  Otherwise, format specifier f is used to print the value.
  Trailing zeros are not printed in the fractional part of a value output with g/G.
  At least one decimal digit is  required for the decimal point to be output.
  Values 0.0000875, 8750000.0, 8.75 and 87.50 are printed as 8.75e-05, 8.75e+06,
  8.75 and 87.5 with the format specifier g.
  Value 0.0000875 is printed with e notation because, when it's converted to 
  exponential notation, its exponent of -5 is less than -4. 
  Value 8750000.0 is printed with e notation because its exponent of 6 is equal
  to the default precision.
  The precision for format specifiers g and G indicates the maximum number of
  significant digits printed, including the digit to the left of the decimal point.
  The value 1234567.0 is printed as 1.23457e+06, using format specifier %g 
  (remember that all floating-point format specifiers have a default precision
  of 6). There are six significant digits in the result.
  The difference between g and G is identical to the difference between e and E 
  when the value is printed in exponential notation—lowercase g causes a lowercase
  e to be output, and uppercase G causes an uppercase E to be output.
  */

  // format specifier g to print float
  printf("Print float  using format specifier %%g: %g\n", f);
  // format specifier g to print double
  printf("Print double using format specifier %%g: %g\n", d);
  // format specifier G to print float
  printf("Print float  using format specifier %%G: %G\n", f);
  // format specifier G to print double
  printf("Print double using format specifier %%G: %G\n", d);

  // format specifier g to print float
  printf("Print float  using format specifier %%g: %g\n", f2);
  // format specifier g to print double
  printf("Print double using format specifier %%g: %g\n", d2);
  // format specifier G to print float
  printf("Print float  using format specifier %%G: %G\n", f2);
  // format specifier G to print double
  printf("Print double using format specifier %%G: %G\n", d2);

  return 0;
}
