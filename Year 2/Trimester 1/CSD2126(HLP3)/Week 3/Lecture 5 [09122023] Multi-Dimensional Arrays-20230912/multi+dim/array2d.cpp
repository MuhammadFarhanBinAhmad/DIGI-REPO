// HLP3 05/31
// array2d.cpp: static and dynamic allocation of 2d arrays ...

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
  void dumpcol(int32_t (*A)[INNER_SIZE], int32_t rows);
  void dump(int32_t **A, int32_t rows, int32_t cols);
}

int main() {
  randomize();

  // statically allocated 3 x 5 array, partially initialized
  int32_t A[3][INNER_SIZE] = { {3,1,4}, {1,5} };
  //dump(A, 3, INNER_SIZE); // error: make sure to know why this function call doesn't compile
  dumpcol(A, 3); // pointer to 1st element of array of 3 elements, where each element
                  // is int[INNER_SIZE]
  std::cout << "----------------------------\n";

  // dynamically allocate M x N array
  int32_t rows = 1 + pick(3, 6)%10, cols = 1 + pick(3, 6)%10;
  int32_t **B = new int32_t* [rows];
  for (int32_t r{}; r < rows; ++r) {
    B[r] = new int32_t[cols];
  }
  // fill dynamically allocated array with values
  for (int32_t r{}; r < rows; ++r) {
    for (int32_t c{}; c < cols; ++c) {
      B[r][c] = pick(1, 100)%100;
    }
  }

  std::cout << "rows=" << rows << ", cols=" << cols << '\n';
  dump(B,rows,cols);
  // the following won't compile - make sure to know why
#if 0
  if (cols == 5) {
    dumpcol(B,rows);
  }
#endif

  // clean up ...
  for (int32_t r{}; r < rows; ++r) {
    delete[] B[r];
  }
  delete[] B;
}

namespace {
// print contents of array of rows elements where each element is an array of 5 int values
// first parameter: A is pointer to first element of array
// second parameter: number of elements in array
void dumpcol(int32_t (*A)[INNER_SIZE], int32_t rows) {
  for (int32_t r{}; r < rows; ++r) {
    for (int32_t c{}; c < INNER_SIZE; ++c) {
      // since A is pointer to 1st element of array, A[r] is element with index r
      // since each element of array has type int [INNER_SIZE], A[r][c] allows us to access
      // a specific element of the int [INNER_SIZE]
      //std::cout << A[r][c] << ' '; 

      // since A is pointer to 1st element of array, *(A+r) is element with index r
      // since each element of array has type int [INNER_SIZE], *(A+r)[c] allows us to access
      // a specific element of the int [INNER_SIZE]
      //std::cout << *(A+r)[c] << ' ';

      // since A is pointer to 1st element of array, *(A+r) is element with index r
      // since each element of array has type int [INNER_SIZE], *(A+r) has type int*
      // therefore, *(*(A+r)+c) allows us to access a specific element of the int [INNER_SIZE],
      std::cout << std::setw(3) << *(*(A+r)+c) << ' '; 
                                
    }
    std::cout << '\n';
  }
}

// print contents of (dynamically allocated) 2d array with
// "rows" count of rows and "cols" count of columns
// first parameter: A is variable that contains address of array of rows elements where
// each element is of type int*. Therefore, A has type int**
// Each element of this array of rows elements points to an array of cols elements, each element of type int
// second and third parameters: rows specifies the number of elements in array whose first element is pointed
// to by parameter A; cols specifies the number of elements in dynamically allocated array that each element of
// [earlier] array is pointing to ...
void dump(int32_t **A, int32_t rows, int32_t cols) {
  for (int32_t r{}; r < rows; ++r) {
    for (int32_t c{}; c < cols; ++c) {
      std::cout << std::setw(3) << A[r][c] << ' ';
    }
    std::cout << '\n';
  }
}
} // end anonymous namespace ...

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
