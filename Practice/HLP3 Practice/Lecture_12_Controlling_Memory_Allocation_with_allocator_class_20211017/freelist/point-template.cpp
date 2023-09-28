/*
CSD2125 10/11
point-template.cpp
This file shows the time for performing the same actions as in point.cpp on 
objects of type Point3D that are now obtained from a memory pool.
The previous version (in point-freelist.cpp) is limited to managing Point3D
objects only. What if we wanted a memory manager for some other class of a
different size? Duplicating the memory management logic for every class will be
an unnecessary waste of resources. If we look at the implementation of the Point3D
memory manager, it becomes apparent that the memory management logic is really
independent of the particular class. The only dependency is the size of the class
object and is a good candidate for a template implementation of a memory pool.
The memory pool in class MemPool<T> manages a pool of available objects of
type T.
*/
#include <iostream>
#include <chrono>
#include <iomanip>

class Timer {
public:
  Timer() : start_time(std::chrono::steady_clock::now()), end_time(start_time) {}
  void Start() { start_time = std::chrono::steady_clock::now(); }
  void End()   { end_time   = std::chrono::steady_clock::now(); }
  std::chrono::steady_clock::time_point Start() const { return start_time; }
  std::chrono::steady_clock::time_point End()   const { return end_time; }
private:
// the two main entities are:
// duration: of time is a specific number of ticks over a time unit. One example
// is a duration such as "3 minutes" or 86,400 seconds (1 day).
// time_point: representing a combination of a duration and a beginning of
// time. A typical example of time_point is "NY Midnight 2000" which is
// described as 1,262,300,400 seconds since January 1, 1970.
// duration and time_point can be added, subtracted, and scaled. For example,
// we can add a duration to a time_point to send a message that we will be
// home in 2 hours.
// steady_clock is a clock with guaranteed increasing time points and is
// therefore convenient for a timer.
  std::chrono::steady_clock::time_point start_time, end_time;
};

std::ostream& operator<<(std::ostream& os, Timer const& rhs) {
  std::chrono::steady_clock::duration exec_time = rhs.End() - rhs.Start();

  os << "Time taken in secs: " << std::fixed << std::setprecision(2) << std::setw(5)
  // for printing something more tangible, let's print the seconds taken by
  // determining milliseconds and divide this by the double value 1000.0
    << std::chrono::duration_cast<std::chrono::milliseconds>(exec_time).count()/1000.0
    << " | millisecs: " << std::setw(6) 
    << std::chrono::duration_cast<std::chrono::microseconds>(exec_time).count()/1000.0
    //<< " | microsecs: " << std::setw(12) 
    //<< std::chrono::duration_cast<std::chrono::nanoseconds>(exec_time).count()/1000.0
    << "\n";
  return os;
}

template <typename T>
class MemPool {
public:
  MemPool(size_t size = expansion_size) { expand_list(size); }
  MemPool(MemPool const&) = delete;
  MemPool& operator=(MemPool const&) = delete;
  ~MemPool();

  inline void* alloc(size_t); // allocate a T element from free list
  inline void  free(void*); // return a T element to free list
private:
  MemPool<T> *next; // next element on free list
  static size_t const expansion_size; // by how much to expand free list
  void expand_list(size_t); // add expansion_size count of free elements to free list
};

template <typename T>
size_t const MemPool<T>::expansion_size {64};

// add new elements to free list: the new elements are allocated from the
// heap and stitched together into a linked list
template <typename T>
void MemPool<T>::expand_list(size_t count) {
  // allocate an object large enough to contain either T or MemPool<T>*.
  size_t size = sizeof(T) > sizeof(MemPool<T>*) ? sizeof(T) : sizeof(MemPool<T>*);
  MemPool<T> *iter = reinterpret_cast<MemPool<T>*>(new char [size]);
  next = iter;
  for (size_t i{1}; i < count; ++i) {
    iter->next =  reinterpret_cast<MemPool<T>*>(new char [size]);
    iter = iter->next;
  }
  iter->next = nullptr;
}

// delete every element by marching down the free list ...
template <typename T>
MemPool<T>::~MemPool() {
  for (MemPool<T> *next_ptr {next}; next_ptr; next_ptr = next) {
    next = next->next;
    delete [] (reinterpret_cast<char*>(next_ptr));
  }
}

// allocate large enough memory for either a T element or a MemPool<T>* element
template <typename T>
inline void* MemPool<T>::alloc(size_t) {
  if (!next) { expand_list(expansion_size); }
  MemPool<T> *head = next;
  next = head->next;
  return head;
} 

// free deallocates a T element by placing it back on the free list
template <typename T>
inline void MemPool<T>::free(void *returnee) {
  MemPool<T> *head = static_cast<MemPool<T>*>(returnee);
  head->next = next;
  next = head;
}

class Point3D {
public:
  Point3D(double dx=1.1, double dy=2.2, double dz=3.3) : x{dx}, y{dy}, z{dz} {}
  std::tuple<double, double, double> Get() const { return {x, y, z}; }

  void* operator new(size_t size)       { return mem_pool->alloc(size); }
  void  operator delete(void *returnee) { mem_pool->free(returnee); }

  static void new_mem_pool()    { mem_pool = new MemPool<Point3D>; }
  static void delete_mem_pool() { delete mem_pool; }
private:
  double x{0.0}, y{0.0}, z{0.0};
  static MemPool<Point3D> *mem_pool;
};

MemPool<Point3D>* Point3D::mem_pool{nullptr};

// driver program
int main() {
  constexpr size_t size{10000}, times{5000};
  Point3D *array_of_ptrs[size];
  Point3D::new_mem_pool();

  Timer t;
  t.Start(); // start timer

  for (size_t j{0}; j < times; ++j) {
    for (size_t i{0}; i < size; ++i) {
      array_of_ptrs[i] = new Point3D(i, j);
    }
    for (size_t i{0}; i < size; ++i) {
      delete array_of_ptrs[i];
    }
  }

  t.End();   // end timer
  std::cout << "timer: " << t; // left-shift operator is overloaded for class Timer

  Point3D::delete_mem_pool();
}
