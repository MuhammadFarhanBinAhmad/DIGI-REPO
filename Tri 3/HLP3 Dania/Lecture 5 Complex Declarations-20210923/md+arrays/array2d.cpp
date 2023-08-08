// array2d.cpp
// -- static and dynamic allocation of 2D arrays
// CSD2125 9/16

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void dump(int **A, int rows, int cols) {
  for (int r=0; r < rows; ++r) {
    for (int c=0; c < cols; ++c)
      cout << A[r][c] << ' ';
    cout << endl;
  }
}


void dump5col(int (*A)[5], int rows) {
  for (int r=0; r < rows; ++r) {
    for (int c=0; c < 5; ++c)
      cout << A[r][c] << ' ';
    cout << endl;
  }
}


int main(void) {
  srand((unsigned)time(0));

  // statically allocated 3 x 5 array, partially initialized
  int A[3][5] = { {3,1,4},
                  {1,5} };
  // dump(A,3,5);
  dump5col(A,3);
  cout << endl;

  // dynamically allocated M x N (ragged) array
  int rows = 1 + rand()%10,
      cols = 1 + rand()%10;
  int **B = new int* [rows];
  for (int r=0; r < rows; ++r)
    B[r] = new int[cols];
  for (int r=0; r < rows; ++r)
    for (int c=0; c < cols; ++c)
      B[r][c] = rand()%10;

  cout << "rows=" << rows << ", cols=" << cols << endl;
  dump(B,rows,cols);
  // if (cols == 5)
  //   dump5col(B,rows);

  for (int r=0; r < rows; ++r)
    delete[] B[r];
  delete[] B;

  return 0;
}

