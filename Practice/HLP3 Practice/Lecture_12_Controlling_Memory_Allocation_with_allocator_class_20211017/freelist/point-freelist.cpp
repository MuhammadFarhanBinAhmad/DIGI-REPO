/*
CSD2125 10/11
point-freelist.cpp
This file shows the time for performing the same actions as in point.cpp on 
objects of type Point3D that are now obtained from a memory pool.
This class defines static member functions that creates a memory pool consisting
of a singly linked list of Point3D objects. The head of the linked list points
to the next available free Point3D object. When a Point3D object is no longer
required, it is added to the head of the linked list. When the linked list is
empty, it is extended with additional Point3D objects.
The Point3D class redefines the behavior of ::operator new(size_t) and
::operator delete(void*) as member functions. Instead of dynamically allocating
and deallocating Point3D objects, the operator new and delete functions will
take and add Point3D objects from the memory pool.
Compile: g++ -std=c++17 point-freelist.cpp
*/
#include <iostream>
#include <chrono>
#include <iomanip>
#include <new>

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

class Point3D {
public:
  Point3D(double dx=1.1, double dy=2.2, double dz=3.3) : x{dx}, y{dy}, z{dz} {}
  std::tuple<double, double, double> Get() const { return {x, y, z}; }

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  static void create_mem_pool() { expand_list(); }
  static void delete_mem_pool();

  struct List { List *next; };
private:
  double x{0.0}, y{0.0}, z{0.0};

// although each element of the free list is a List structure, it
// it is also a Point3D object. When we create an element, we allocate it
// large enough to contain a Point3D object. We will then use the Point3D
// object to point to the next object on the free list. We do that by casting
// the object into a pointer to type List.
  static List *free_list; // points to a free list of Point3D objects
  static size_t expansion_size; // by how much to expand free list
  static void expand_list();
};

// static data member is now defined ...
Point3D::List* Point3D::free_list {nullptr};
size_t Point3D::expansion_size {1280};

// operator new allocates a new Point3D object from the free list. If the
// free list is empty, it will be expanded. Then, we pick off the head of
// the free list and return it by adjusting the free list pointer.
inline void* Point3D::operator new(size_t size) {
  if (nullptr == free_list) { expand_list(); }
  List *head = free_list;
  free_list = head->next;
  return head;
}

// operator delete returns Point3D object returnee to the free list
// by simply adding it to the front of the free list.
inline void Point3D::operator delete(void *returnee) {
  List *head = static_cast<List*>(returnee);
  head->next = free_list;
  free_list = head;
}

void Point3D::expand_list() {
  // we must allocate an object large enough to contain either a
  // Point3D object or a List*.
  size_t size = sizeof(Point3D) > sizeof(List*)
                ? sizeof(Point3D) : sizeof(List*);

  // use ::operator new to allocate a free list element ... 
  List *runner = reinterpret_cast<List*>(new char [size]);
  free_list = runner; // free_list has exhausted free Point3D objects ...
  for (size_t i{0}; i < expansion_size; ++i) {
    runner->next = reinterpret_cast<List*>(new char [size]);
    runner = runner->next;
  }
  runner->next = nullptr;
}

void Point3D::delete_mem_pool() {
  for (List *next = free_list; next != nullptr; next = free_list) {
    free_list = free_list->next;
    delete [] (reinterpret_cast<char*>(next));
  }
}

// driver program
int main() {
  constexpr size_t size{10000}, times{5000};
  Point3D *array_ptrs[size];
  Point3D::create_mem_pool();

  Timer t;
  t.Start(); // start timer

  for (size_t j{0}; j < times; ++j) {
    for (size_t i{0}; i < size; ++i) {
      array_ptrs[i] = new Point3D(i, j);
    }
    for (size_t i{0}; i < size; ++i) {
      delete array_ptrs[i];
    }
  }

  t.End();   // end timer
  std::cout << "timer: " << t; // left-shift operator is overloaded for class Timer

  Point3D::delete_mem_pool();
}
