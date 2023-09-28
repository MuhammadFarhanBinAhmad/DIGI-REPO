/*
CSD2125 10/11
point.cpp
This file shows a baseline time for performing some actions on objects
of type Point3D. We'll use these baseline measurements to compare with
the same actions performed on objects that are dynamically allocated
only once.
Compile: g++ -std=c++17 point.cpp
*/
#include <iostream>
#include <iomanip>
#include <chrono>

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
private:
  double x{0.0}, y{0.0}, z{0.0};
public:
  Point3D(double dx=1.1, double dy=2.2, double dz=3.3) : x{dx}, y{dy}, z{dz} {}
  std::tuple<double, double, double> Get() const { return {x, y, z}; }
};

// driver program
int main() {
  constexpr size_t size{10000}, times{5000};
  Point3D *array_ptrs[size];

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
}
