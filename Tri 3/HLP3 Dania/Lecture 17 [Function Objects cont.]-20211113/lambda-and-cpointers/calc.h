// CSD2125 11/09
// part of program to show that lambdas can be used to
// replace C style functions ...
// this header file declares functions to be callable from
// both C and C++ functions
#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

bool fun_max(int lhs, int rhs);
bool fun_min(int lhs, int rhs);
bool compare(int lhs, int rhs, bool (*func_ptr)(int, int));

#ifdef __cplusplus
}
#endif
