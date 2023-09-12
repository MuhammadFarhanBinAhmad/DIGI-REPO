// HLP3 05/31
// array1d2d.cpp:
// statically allocated 2D array is just a 1D array where each element
// is a 1D array with inner 1D arrays stored contiguously.

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
  constexpr int32_t INNER_SIZE {3};
  void dump_1d_block(int8_t const *A, int32_t count);
  void dump_1d_block_rows_cols(int8_t const *A, int32_t rows, int32_t cols);
  void dump_2d_block(int8_t (*p)[INNER_SIZE], int32_t rows);
}

int main() {
  randomize();

  // statically allocated 2D array
  int8_t A[2][INNER_SIZE] = {{'a','b','c'}, {'d','e','f'}};

  // print 2D array as 1D array with 2 x INNER_SIZE elements ...
  dump_1d_block(&A[0][0], sizeof(A)/sizeof(int8_t)); std::cout << '\n';

  // print 2D array as 1D array with 6 elements broken up into 2 sets of 3 ints each ...
  dump_1d_block_rows_cols(&A[0][0], 2, INNER_SIZE); std::cout << '\n';

  // print 2d array as array of 2 elements with each element char[INNER_SIZE]
  dump_2d_block(A, 2); std::cout << '\n';

  // dynamically allocated 1D array, viewed as a 2D array
  int32_t rows = 1 + pick(2,5)%10, cols = 1 + pick(3,6)%10, total = rows*cols;
  int8_t *B = new int8_t[total];
  for (int32_t i{}; i < total; ++i) { // fill 1D arrsay with elements ...
    B[i] = (int8_t)('a' + pick(1,1000)%26);
  }
  std::cout << "rows=" << rows << ", cols=" << cols << '\n';
  // print dynamically allocated 1D array with rows x cols elements broken up into
  // rows number of sets of cols ints each ...
  dump_1d_block_rows_cols(B, rows, cols);

  // clean up ...
  delete[] B;
}

namespace {
// printing the 2d array as a 1d array
// note: there's no way for us to know the number of rows and number of columns;
// therefore, the entire set of values are printed as a 1d array ...
void dump_1d_block(int8_t const *A, int32_t count) {
  for (int32_t i{}; i < count; ++i) {
    std::cout << A[i] << ' ';
  }
  std::cout << '\n';
}

// printing 2d array as 1d array except that we're given shape of 2d array
void dump_1d_block_rows_cols(int8_t const *A, int32_t rows, int32_t cols) {
  for (int32_t r{}; r < rows; ++r) {
    for (int32_t c{}; c < cols; ++c) {
      std::cout << std::setw(2) << std::left << A[r*cols+c] << ' ';
    }
    std::cout << std::right << '\n';
  }
}

// printing 2d table as array of "rows" elements with each element a "int8_t[3]"
// note: the following declaration is usually written as:
// void dump_2d_block(int8_t p[][INNER_SIZE], int32_t rows) but that syntactic
// sugercoating is converted by the compiler to this declaration:
void dump_2d_block(int8_t (*p)[INNER_SIZE], int32_t rows) {
  for (int32_t r{}; r < rows; ++r) {
    for (int32_t c{}; c < INNER_SIZE; ++c) {
      std::cout << std::setw(2) << std::left << *(*(p+r) + c) << ' ';
    }
    std::cout << std::right << '\n';
  }
}
}

namespace {
void dump_ptr(int8_t const *A, int32_t rows, int32_t cols) {
  for (int32_t r{}; r < rows; ++r) {
    for (int32_t c{}; c < cols; ++c) {
      std::cout << A[r*cols+c] << ' ';
    }
    std::cout << '\n';
  }
}

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
