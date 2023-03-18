#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
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

// define new name for type unsigned long int
using uli64 = unsigned long int;

/*
This function profile the push_back member function of a specific sequence
container class. Note that vector, deque, and list are the only container
classes that provide this member function.
*/
template <typename Cont>
void profile_pushback(Cont& c, uli64 max_iters, std::string const& pre) {
  Timer t;
  t.Start(); // start timer
  for (uli64 i{0}; i < max_iters; ++i) {
    c.push_back(i);
  }
  t.End();   // end timer
  std::cout << pre << t; // left-shift operator is overloaded for class Timer
}

/*
This function profile the push_front member function of a specific sequence
container class. Note that deque, forward_list, and list are the only container
classes that provide this member function.
*/
template <typename Cont>
void profile_pushfront(Cont& c, uli64 max_iters, std::string const& pre) {
  Timer t;
  t.Start(); // start timer
  for (uli64 i{0}; i < max_iters; ++i) {
    c.push_front(i);
  }
  t.End();   // end timer
  std::cout << pre << t; // left-shift operator is overloaded for class Timer
}

int main() {
  uli64 max_iters = 10'000'000; // number of values to push back ...

std::cout << "PROFILING push_back member function ...\n";
{ // specify local scope to reuse names ...
  // only vector, deque, and list provide push_back member function ...
  // this is an important concept of the STL: each container provides only
  // those member functions that provide the most efficient performance!!!
  std::vector<uli64> vs;
  profile_pushback(vs,  max_iters, "vector: ");
  std::deque<uli64> ds;
  profile_pushback(ds,  max_iters, " deque: ");
  std::list<uli64>  ls;
  profile_pushback(ls,  max_iters, "  list: ");
  
  // using reserve to avoid unnecessary reallocations
  std::vector<uli64> vs2; vs2.reserve(max_iters);
  profile_pushback(vs2, max_iters, "vector: ");
} // end of local scope ...


std::cout << "\nPROFILING push_front member function ...\n";
{ // specify local scope to reuse names ...
  // only deque, list, and forward_list provide push_front member function ...
  std::deque<uli64> ds;
  profile_pushfront(ds,  max_iters, "       deque: ");
  std::list<uli64> ls;
  profile_pushfront(ls,  max_iters, "        list: ");
  std::forward_list<uli64> fs;
  profile_pushfront(fs,  max_iters, "forward_list: ");
} // end of local scope ...
}
