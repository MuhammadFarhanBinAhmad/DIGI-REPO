// In this C header file, use extern "C" specifier for functions
// we wish to export to C++.
// CSD2125
// 09/23/2021

#ifndef CALC_H
#define CALC_H

// __cplusplus is a macro exported by all C++ compilers but
// not by C compilers.
// Therefore the following extern "C" will be available only
// to C++ compilers and it says "don't mangle the function
// names add and mul
#ifdef __cplusplus
extern "C" {
#endif

  int add(int, int);
  int mul(int, int);

#ifdef __cplusplus
}
#endif

#endif // CALC_H
