// array3d.cpp
// -- static and dynamic 3D arrays
// CSD2125 09/16

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void dump(char *A, int frms, int rows, int cols) {
  for (int f=0; f < frms; ++f) {
    for (int r=0; r < rows; ++r) {
      for (int c=0; c < cols; ++c)
        cout << A[rows*cols*f+cols*r+c] << ' ';
      cout << endl;
    }
    cout << endl;
  }
}

int main(void) {
  srand(unsigned(time(0)));

  // statically allocated 3D array
  char A[3][2][4] = { { {'a','b','c','d'},
                        {'e','f','g','h'} },
                      { {'i','j','k','l'},
                        {'m','n','o','p'} },
                      { {'q','z','s','t'},
                        {'u','v','w','x'} } };
  A[2][0][1] = 'r';
  dump(&A[0][0][0],3,2,4);
  cout << endl;

  // dynamically allocated 1D array, treated as a 3D array;
  int frms = 1 + rand()%5,
      rows = 1 + rand()%5,
      cols = 1 + rand()%10,
      total = frms*rows*cols;
  char *B = new char[total];
  cout << "frms=" << frms
       << ", rows=" << rows
       << ", cols=" << cols << endl;

  for (int i=0; i < total; ++i)
    B[i] = 'a' + rand()%26;
  int f = rand()%frms,
      r = rand()%rows,
      c = rand()%cols;
  // B[f][r][c] = 'r';
  B[rows*cols*f+cols*r+c] = 'r';
  cout << "B[" << f << "][" << r << "][" << c << "] = 'r'" << endl;

  dump(B,frms,rows,cols);
  delete[] B;
}

