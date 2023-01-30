// CSD1121 11/16/2022
// This source file illustrates the use of 2D arrays [or 1D array of 1D arrays]
// in solving problems consisting of multi-dimensional data.
// Next week, we'll continue to review concepts related to multi-dimensional arrays
// and pointers and remove the restriction that this program will only work for
// for those scenarios where the number of students and the number of quizzes
// is known at compile-time.

#include <stdio.h>
#include <stdbool.h>

enum {NUM_STUDENTS = 3, NUM_QUIZZES = 4};

bool read_grades(char const *file_name, int grades[][NUM_QUIZZES], int rows);
void avg_quiz(int grades[][NUM_QUIZZES], int rows, double *avg);
void print(double *first, double *last, char const *prefix_msg);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: grades.exe input-file-containing-grades\n");
    return 0;
  }

  int grades[NUM_STUDENTS][NUM_QUIZZES];

  if (read_grades(argv[1], grades, NUM_STUDENTS) == false) {
    fprintf(stderr, "Unable to fill grades[][] with grades from %s!!!\n", argv[1]);
    return 0;
  }

  double avg[NUM_STUDENTS];
  avg_quiz(grades, NUM_STUDENTS, avg);
  print(avg, avg+NUM_STUDENTS, "Average quiz grade per student:\n");

  return 0;
}

bool read_grades(char const *file_name, int grades[][NUM_QUIZZES], int rows) {
  FILE *ifs = fopen(file_name, "r");
  if (!ifs) {
    return false;
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < NUM_QUIZZES; ++j) {
      fscanf(ifs, "%d", &grades[i][j]);
    }
  }
  fclose(ifs);

  return true;
}

void avg_quiz(int grades[][NUM_QUIZZES], int rows, double *avg) {
  for (int i = 0; i < rows; ++i) {
    int sum = 0;
    for (int j = 0; j < NUM_QUIZZES; ++j) {
      sum += grades[i][j];
    }
    avg[i] = (double)sum/(double)NUM_QUIZZES;
  }
}

void print(double *first, double *last, char const *prefix_msg) {
  fprintf(stdout, "%s", prefix_msg);
  int i = 0;
  while (first != last) {
    fprintf(stdout, "Student ID %d: %.2f\n", i++, *first++);
  }
}
