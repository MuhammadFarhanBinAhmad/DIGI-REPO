/*
* bmi-in-lbs-inches.c - source file containing C code for computing
* body mass index (BMI) given weight (in pounds) and height (in inches).
*
* Input from standard input: Weight (in lbs) and height (in inchs)
* Side effect of program: Body mass index as a number and relationship 
* between weight and height.
*
* Always compile with full-suite of options:
* gcc -std=c11 -pedantic-errors -Wstrict-prototypes -Wall -Wextra -Werror bmi-in-lbs-inches.c -o bmi-in-lbs-inches.out
*
* Run: ./bmi-in-lbs-inches.out
* 
* Prasanna Ghali
* Original program written for HLP1 on 09/01/2020
*/
#include <stdio.h>

// conversion units from 1 pound to kg and 1 inch to meter
#define KG_PER_LB      (0.453592) // 1 pound to kg
#define METER_PER_INCH (0.0254)   // 1 inch to meter

double compute_bmi(double w, double h);
void print_bmi_msg(double w, double h, double bmi);

int main(void) {
  printf("Enter your weight in lbs: ");
  double weight;
  scanf("%lf", &weight);
  printf("Enter your height in inches: ");
  double height = 0.0;
  scanf("%lf", &height);

  double bmi = compute_bmi(KG_PER_LB*weight, METER_PER_INCH*height);
  print_bmi_msg(KG_PER_LB*weight, METER_PER_INCH*height, bmi);

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
