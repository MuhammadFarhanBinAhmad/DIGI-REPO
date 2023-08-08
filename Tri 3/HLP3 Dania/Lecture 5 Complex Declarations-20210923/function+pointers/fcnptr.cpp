/* fcnptr.cpp
** -- function pointers
** CSD2125 09/16
*/

#include <iostream>
#include <ctime>

void Modify(int *array, int count, int (*op)(int)) {
  for (int i{}; i < count; ++i) {
    array[i] = op(array[i]);
  }
}

// RAND_MAX: 65535
int Rand100(int n) { return (rand()*n) % 100; }
int Add4(int n) { return n+4; }
int Dump(int n) { std::cout << n << " "; return n; }

int main() {
  int (*fparray[])(int) {Rand100, Add4};
  constexpr int SIZE {8};
  int A[SIZE] {0,1,2,3,4,5,6,7};

  for (int i=0; i < SIZE; ++i) {
    std::cout << A[i] << " ";
  }
  std::cout << "\n";

  for (int i{}; i < SIZE; ++i) {
    A[i] += 4;
  }
  for (int i=0; i < SIZE; ++i) {
    std::cout << A[i] << " ";
  }
  std::cout << "\n";

  srand((unsigned)time(NULL));

  Modify(A, SIZE, Rand100);
  Modify(A, SIZE, Dump);
  std::cout << "\n";

  Modify(A, SIZE, Add4);
  Modify(A, SIZE, Dump);
  std::cout << "\n";

  int n = 1 + rand()%10;
  int *B = new int [n*sizeof(int)];

  for (int i=0; i < 2; ++i) {
    Modify(B, n, fparray[i]);
    Modify(B, n, Dump);
    std::cout << "\n";
  }

  delete [] B;
}






