// since Vec is a class template, this file containing definitions of
// member functions of Vec<T> must be included into vec.h

// static data members and member functions ...
template <typename T> size_t Vec<T>::copy{0};
template <typename T> size_t Vec<T>::move{0};
template <typename T> size_t Vec<T>::CopyCount() { return copy; }
template <typename T> size_t Vec<T>::MoveCount() { return move; }

template <typename T>
Vec<T>::Vec(size_t sz) : ptr{new T[sz]{}}, len{sz} {
  ++copy;
#ifdef VEC_DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

template <typename T>
Vec<T>::Vec(Vec const& rhs) : Vec{rhs.len} {
  ++copy;
  std::copy(rhs.ptr, rhs.ptr+rhs.len, ptr);
#ifdef VEC_DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

template <typename T>
Vec<T>::~Vec() {
#ifdef VEC_DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  delete [] ptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec const& rhs) {
  Vec<T> copy{rhs};
  swap(copy);
#ifdef VEC_DEBUG
  std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
  return *this;
}

#ifdef VEC_MOVE
template <typename T>
Vec<T>::Vec(Vec&& rhs) noexcept : ptr{rhs.ptr}, len{rhs.len} {
  ++move;
  rhs.ptr = nullptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec&& rhs) noexcept {
  ++move;
  if (this &= rhs) {
    swap(rhs);
  }
  return *this;
}
#endif

template <typename T>
void Vec<T>::push_back(T const& element) {
  Vec<T> tmp{len+1};
  std::copy(ptr, ptr+len, tmp.ptr);
  tmp[len] = element;
  swap(tmp);
}

template <typename T>
void Vec<T>::swap(Vec& rhs) noexcept {
  std::swap(ptr, rhs.ptr);
  std::swap(len, rhs.len);
}

template <typename T>
void swap(Vec<T>& lhs, Vec<T>& rhs) noexcept {
  lhs.swap(rhs);
}
