/*
CSD2125 10/11
uptr-cont.cpp
We've previously seen that std::unique_ptr<T> implements an unique ownership
concept - an object of type T can be owned by only one unique_ptr<T> at a time.
We've also previously mentioned that the basic mechanism of unique_ptr<T> is so
simple that it costs nothing to use.
Now, let's consider the question of whether non-trivial objects [in terms of
memory used] should be stored in containers by value or by pointer.
The profiler below shows that many standard algorithms such as sort have
better performance with containers of pointers rather than containers of values.
Why? Because many algorithms need to shuffle around objects through copying.
And, copying non-trivial objects is much more expensive than copying pointers.
However, we've previously seen that raw pointers cause problems [memory leaks,
double-deletion, use-after-delete, and so on]. As the following code illustrates,
what we'd really like to do is to replace a container of raw pointers with a
container of unique_ptr<T>s. Since unique_ptr<T>s are as efficient as raw
pointers we get the efficiencies of pointers with the additional advantage of
writing code that adheres to principles of RAII.

Note: Compile code [with your compiler] with highest optimization setting ...
*/
#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <limits>

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

/*
The random number generators in Modern C++ provide a lot of flexibility
which is very useful but somewhat overwhelming for beginners. The following
is a set of beginner-friendly functions that are sufficient for many practical
purposes:
*/
namespace {

// std::default_random_engine provides a mathematical formula that allow the
// generation of statistically random values.
std::default_random_engine& global_urng() {
  static std::default_random_engine u{};
  return u;
}

// The random engine will return the next value from a sequence of values.
// But, how will it get its first value? The random device ignites the
// random engine with a seed.
void randomize() {
  static std::random_device rd{};
  global_urng().seed(rd());
}

// we want uniformly distributed int values
uint32_t pick(uint32_t from, uint32_t thru) {
  static std::uniform_int_distribution<uint32_t> d{};
  using param_t = std::uniform_int_distribution<uint32_t>::param_type;
  return d(global_urng(), param_t{from, thru});
}

/*
You only need to remember the following two functions:
a) randomize: make the numbers really random by initializing the generator's seed.
b) pick(uint32_t a, uint32_t b): Give an uint32_t in the interval [a, b] when a and b are uint32_t
*/
}

struct PS {
  PS(double ax, double ay, double az) : x{ax}, y{ax}, z{az} {}
  double x{}, y{}, z{};
  double pts[100][3]={{0.0,0.0,0.0}};
};

// compare two objects of type PS by reference and by pointer ...
bool cmp_by_ref(PS const& lhs, PS const& rhs) {
  return (lhs.x*lhs.x+lhs.y*lhs.y+lhs.z*lhs.z) < (rhs.x*rhs.x+rhs.y*rhs.y+rhs.z*rhs.z);
}

bool cmp_by_ptr(PS const *lhs, PS const *rhs) {
  return (lhs->x*lhs->x+lhs->y*lhs->y+lhs->z*lhs->z) < (rhs->x*rhs->x+rhs->y*rhs->y+rhs->z*rhs->z);
}

bool cmp_by_uniqueptr(std::unique_ptr<PS> const& lhs, std::unique_ptr<PS> const& rhs) {
  return (lhs->x*lhs->x+lhs->y*lhs->y+lhs->z*lhs->z) < (rhs->x*rhs->x+rhs->y*rhs->y+rhs->z*rhs->z);
}

int main() {
  randomize();
  uint32_t min_range {std::numeric_limits<uint32_t>::min()};
  uint32_t max_range {std::numeric_limits<uint32_t>::max()};
  
  std::vector<PS>  vec_val;
  std::vector<PS*> vec_ptr;
  std::vector<std::unique_ptr<PS>> vec_uniptr;

  // populate both containers ...
  constexpr int N {100'000};
  for (int i{}; i < N; ++i) {
    double x = static_cast<double>(pick(min_range, max_range));
    double y = static_cast<double>(pick(min_range, max_range));
    double z = static_cast<double>(pick(min_range, max_range));
    vec_val.push_back(PS(x, y, z));
    vec_ptr.push_back(new PS(x, y, z));
    vec_uniptr.push_back(std::make_unique<PS>(x, y, z));
  }

  Timer t; t.Start();
  std::sort(vec_val.begin(), vec_val.end(), cmp_by_ref);
  t.End(); std::cout << "vec_val sort: " << t;

  t.Start();
  std::sort(vec_ptr.begin(), vec_ptr.end(), cmp_by_ptr);
  t.End(); std::cout << "vec_ptr sort: " << t;

  t.Start();
  std::sort(vec_uniptr.begin(), vec_uniptr.end(), cmp_by_uniqueptr);
  t.End(); std::cout << "vec_uniptr sort: " << t;

  // release memory pointed to by elements of vec_ptr
  for (std::vector<PS*>::size_type i{}; i < vec_ptr.size(); ++i) {
    delete vec_ptr[i];
  }
}

