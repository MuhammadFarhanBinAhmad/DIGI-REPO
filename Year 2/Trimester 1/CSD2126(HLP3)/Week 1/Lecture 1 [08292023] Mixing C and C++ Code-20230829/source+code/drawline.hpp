// pghali for HLP3
// 08/30/2022
// In this C++ header file, use extern "C" specifier for functions
// we wish to export to C so that their names are not mangled.

#ifndef DRAWLINE_HPP
#define DRAWLINE_HPP

// __cplusplus is a macro exported by all C++ compilers but
// not by C compilers.
// Therefore the following extern "C" will be available only
// to C++ compilers and it says "don't mangle the function
// name draw_line.
#ifdef __cplusplus
extern "C"
#endif

int draw_line(int, int);

#endif //DRAWLINE_HPP
