#include <stdio.h>
#define MAX_STUDENT_COUNT 1000

int read_data(double array[], int max_num_vales)
{
    int i = 0;
    double num;
    while ( (scanf("%lf", &num) != EOF) && i < max_array_size ) 
    {
        array[i++] = num;
    }
    return i;
}
int main(void) {
// fill grades with values
double grades[1000];
int count = read_data(grades, MAX_STUDENT_COUNT);
// print grades to standard output
for (int i = 0; i < count; ++i) {
printf("i: %.2f\n", i, grades[i]);
}
return 0;
}
