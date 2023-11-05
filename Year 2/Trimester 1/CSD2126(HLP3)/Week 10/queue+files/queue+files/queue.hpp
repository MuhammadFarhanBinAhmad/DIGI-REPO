#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace HLP3 {

class Queue {
public:
  using value_type = char;
  using reference  = value_type&;
  using const_reference = const value_type&;
  using pointer    = value_type*;
  using const_pointer = const value_type*;
  using size_type = unsigned long;

  Queue(size_type size);
  Queue(const Queue& rhs);
  ~Queue();

  Queue& operator=(const Queue&rhs);

  void push(value_type cont);
  void pop();

  void swap(Queue& rhs);

  reference front();
  reference back();
  
  size_type front_index() const;
  size_type back_index() const;
  size_type capacity() const;
  size_type size() const;
  pointer c_buff() const;
  bool empty() const;
  bool full() const;

  private:
  size_type capacity_;
  size_type front_;
  size_type size_;
  pointer buffer_;
};

void swap(Queue& lhs, Queue& rhs);
// declare necessary non-member function(s) ...

}
#endif
