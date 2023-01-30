/*
* bmi-in-kg-meters.c - source file containing C code for computing
* body mass index (BMI) given weight (in kg) and height (in meters).
*
* Input from standard input: Weight (in kg) and height (in meters)
* Side effect of program: Body mass index as a number and relationship 
* between weight and height.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror bmi-in-kg-meters.c -o bmi-in-kg-meters.out
*
* Run: ./bmi-in-kg-meters.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

double compute_bmi(double w, double h);
void print_bmi_msg(double w, double h, double bmi);

int main(void) {
  printf("Enter your weight in kg: ");
  double weight;
  scanf("%lf", &weight);
  printf("Enter your height in m: ");
  double height = 0.0;
  scanf("%lf", &height);

  double bmi = compute_bmi(weight, height);
  print_bmi_msg(weight, height, bmi);

  return 0;
}

double compute_bmi(double weight_in_kg, double height_in_meter) {
  return weight_in_kg/(height_in_meter * height_in_meter);
}

void print_bmi_msg(double weight, double height, double bmi) {
  printf("Weight: %f (kg) | Height: %f (meter) | BMI: %f\n",
          weight, height, bmi);
  if (bmi < 18.5) {
    printf("Weight for height is underweight.\n");
  } else if (bmi < 24.9) {
    printf("Weight for height is normal.\n");
  } else if (bmi < 29.9) {
    printf("Weight for height is overweight.\n");
  } else {
    printf("Weight for height is obese.\n");
  }
}
