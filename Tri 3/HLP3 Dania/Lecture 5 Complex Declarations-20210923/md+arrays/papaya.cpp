#include <iostream>

using mango = int [5];

int fruit(int X[][5], int r, int c) {
  return X[r][c];
}

int fruit2(int (*X)[5], int r, int c) {
  return (*(X+r))[c]; // X[r][c]
}

int fruit3(int (*X)[4][5], int f, int r, int c) {
  return X[f][r][c];
}

int main() {
  mango papaya[4] {{1,2,3,4,5}, {11, 21, 31, 41, 51}, {22, 32, 42, 52, 62}};
  std::cout << fruit(papaya, 1, 2) << "\n";
  int kiwi[4][5] {{1,2,3,4,5}, {11, 21, 31, 41, 51}, {22, 32, 42, 52, 62}};
  std::cout << fruit2(kiwi+1, 1, 2) << "\n";

  int pear[3][4][5] = {
    {{1,2,3,4,5}, {11, 21, 31, 41, 51}, {22, 32, 42, 52, 62}, {33, 43, 53, 63, 73}},
    {{101,201,301,401,501}, {110, 210, 310, 410, 510}, {220, 320, 420, 520, 620}, {330, 430, 530, 630, 730}},
  };
  int (*p)[4][5] = pear+1;
  std::cout << "pear[1][2][3]: " << (*p)[2][3] << "\n";
  std::cout << fruit3(pear, 1, 2, 3) << "\n";

  int *p60 = new int [60];
  for (int f = 0; f < 3; ++f) {
    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 5; ++c) {
        p60[f*4*5 + r*5 + c] = pear[f][r][c];
      }
    }
  }

  std::cout << p60[1*4*5 + 2*5 + 3] << "\n";
}
