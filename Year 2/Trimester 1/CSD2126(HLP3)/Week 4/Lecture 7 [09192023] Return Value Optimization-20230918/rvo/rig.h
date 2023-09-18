// CSD2125/CS225 05/22/2018
// Contains definition of class Rig that will be used to study RVO in GCC and MSVC

#include <cstdint>

#ifndef RIG_H
#define RIG_H

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__ 
#endif

struct Rig {
  int32_t mi{};
  static int32_t ctr;

  Rig(int i=0);
  Rig(Rig const& rhs);
  ~Rig();
  Rig& operator=(Rig const& rhs);

  void Mi(int32_t x) { mi = x; }
  int32_t Mi() const { return mi; }
};

#endif
