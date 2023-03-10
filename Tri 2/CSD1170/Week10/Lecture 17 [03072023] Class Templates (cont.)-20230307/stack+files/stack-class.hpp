// HLP2: stack-class.hpp
// Definition of classes StackChar and StackStr
#include <cstddef> // for size_t
#include <string>  // for std::string

class StackChar {
public:
  using value_type      = char;
  using size_type       = size_t;
  using reference       = value_type&;
  using const_reference = value_type const&;

public:
  explicit StackChar(size_type sz); // single-arg conversion ctor
  StackChar(StackChar const& rhs);  // copy ctor
  ~StackChar();                     // dtor

  void push(const_reference val);   // push element
  void pop();                       // pop element
  reference top();                  // return element
  const_reference top() const;      // return element
  bool empty() const;               // return whether stack is empty
  size_type size() const;
  size_type max_size() const;

private:
  size_type  max_sz;  // maximum possible number of elements in stack
  size_type  top_idx; // index (in memory pointed to by v) to top of stack
  value_type *v;      // pointer to 1st element in block of memory on free store
};

class StackStr {
public:
  using value_type = std::string;
  using size_type  = size_t;
  using reference  = value_type&;
  using const_reference = value_type const&;

public:
  explicit StackStr(size_type sz); // single-arg conversion ctor
  StackStr(StackStr const& rhs);  // copy ctor
  ~StackStr();                     // dtor

  void push(const_reference val);
  void pop();
  reference top();
  const_reference top() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

private:
  size_type  max_sz;  // maximum possible number of elements in stack
  size_type  top_idx; // index (in memory pointed to by v) to top of stack
  value_type *v;      // pointer to 1st element in block of memory on free store
};
