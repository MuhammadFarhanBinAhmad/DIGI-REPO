/*
CSD2125 10/05
Not-so-clever class design to abstract dynamic arrays.
Unlike std::vector<>, this class combines memory allocation with
initialization.
*/
#ifndef VEC_H
#define VEC_H

#include <cstddef> // for size_t
#include <algorithm>
#include <iostream>

template <typename T>
class Vec {
public:
  explicit Vec(size_t sz);
  Vec(Vec const& rhs);
  Vec& operator=(Vec const& rhs);
  void push_back(T const& element);
  ~Vec();

#ifdef VEC_MOVE
  Vec(Vec&& rhs) noexcept;
  Vec& operator=(Vec&& rhs) noexcept;
#endif

  void swap(Vec& rhs) noexcept;
  T& operator[](size_t idx) { return ptr[idx]; }
  T const& operator[](size_t idx) const { return ptr[idx]; }
  size_t size() const noexcept { return len; }

  static size_t CopyCount();
  static size_t MoveCount();

private:
  T *ptr;
  size_t len;

  static size_t copy;
  static size_t move;
};

template <typename T>
void swap(Vec<T>& lhs, Vec<T>& rhs) noexcept;

#include "vec.cpp"

#endif
