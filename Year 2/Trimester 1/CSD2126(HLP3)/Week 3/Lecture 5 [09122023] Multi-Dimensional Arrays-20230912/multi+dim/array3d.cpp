// HLP3 09/16
// array3d.cpp: static and dynamic 3D arrays

#include <iostream>
#include <iomanip>
#include <random>
#include <cstdint>

// C++ random stuff ...
namespace {
  // std::default_random_engine provides math formula for generating random values.
  std::default_random_engine& global_urng(); 
  // ignite the random engine with a seed.
  void randomize();
  // for uniformly distributed int32_t values
  uint32_t pick(uint32_t from, uint32_t thru);
}

// array stuff being discussed ...
namespace {
  constexpr int32_t INNER_SIZE {4};
  constexpr int32_t OUTER_SIZE {2};
  void dump_1d_as_3d(char *A, int frms, int rows, int cols);
}

int main() {
  randomize();

  // statically allocated 3D array
  char A[3][OUTER_SIZE][INNER_SIZE] = { 
                                        { {'a','b','c','d'}, {'e','f','g','h'} },
                                        { {'i','j','k','l'}, {'m','n','o','p'} },
                                        { {'q','z','s','t'}, {'u','v','w','x'} }
                                      };
  A[2][0][1] = 'r';
  dump_1d_as_3d(&A[0][0][0], 3, OUTER_SIZE, INNER_SIZE); std::cout << '\n';

  // dynamically allocated 1D array, treated as a 3D array;
  int frms = 1 + pick(2, 5)%5, rows = 1 + pick(2, 5)%5, cols = 1 + pick(2, 5)%5,
      total = frms*rows*cols;
  char *B = new char[total];
  std::cout << "frms=" << frms << ", rows=" << rows << ", cols=" << cols << '\n';
  for (int i{}; i < total; ++i) {
    B[i] = 'a' + rand()%26;
  }
  int f = pick(2, 5)%frms, r = pick(3, 6)%rows, c = pick(4, 8)%cols;
  // B[f][r][c] = 'r';
  B[rows*cols*f+cols*r+c] = 'r';
  std::cout << "B[" << f << "][" << r << "][" << c << "] = 'r'" << '\n';

  dump_1d_as_3d(B,frms,rows,cols);
  delete[] B;
}

namespace {
// view a 1d array with frms x rows x cols contiguous elements
// as 3d array [frms][rows][cols]
void dump_1d_as_3d(char *A, int frms, int rows, int cols) {
  for (int f{}; f < frms; ++f) {
    for (int r{}; r < rows; ++r) {
      for (int c{}; c < cols; ++c) {
        std::cout << A[rows*cols*f+cols*r+c] << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
}
} // end anonymous namespace 

namespace {
// std::default_random_engine provides a mathematical formula that allow the
// generation of statistically random values.
std::default_random_engine& global_urng() {
  static std::default_random_engine u{};
  return u;
}

// The random engine will return the next value from a sequence of values.
// But, how will it get its first value? The random device ignites the
// random engine with a seed.
void randomize() {
  static std::random_device rd{};
  global_urng().seed(rd());
}

// we want uniformly distributed int32_t values
uint32_t pick(uint32_t from, uint32_t thru) {
  static std::uniform_int_distribution<uint32_t> d{};
  using param_t = std::uniform_int_distribution<uint32_t>::param_type;
  return d(global_urng(), param_t{from, thru});
}
} // end anonymous namespace
