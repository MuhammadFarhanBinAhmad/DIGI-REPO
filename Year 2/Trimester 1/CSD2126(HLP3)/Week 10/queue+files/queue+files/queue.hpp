/*****************************************************************/ /**
  * \file	queue.hpp
  * \brief	A circular buffer is a fixed-size array that behaves as though the first and last element were
            connected to form a virtual circular memory layout. Such a circular buffer can be treated as a
            finite-sized queue that never gets full and never grows past a certain size. Instead, new elements
            replace the oldest elements. This first-in-first-out [FIFO] mechanism lets you keep track of the
            most recent values in some stream of numbers, automatically throwing away older ones as you
            add new ones. Its main benefit is that you don't need a large amount of memory to retain data, as
            older entries are overwritten by newer ones. Circular buffers are used in I/O buffering, bounded
            logging [when you only want to retain the most recent messages], buffers for asynchronous
            processing, and many other applications
  *
  * \author	 FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
  *
  * \note    I like this assigment, feel like something i will do during the "holiday" as revision
  *          just minus making the driver. I wonder what use for circular buffer
  *
  * \date	06-NOV-2023
 ***********************************************************************/
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
  const_reference front() const;
  const_reference back() const;

  size_type front_index() const;
  size_type back_index() const;
  size_type capacity() const;
  size_type size() const;
  pointer c_buff() const;

  bool empty() const;
  bool full() const;
  bool empty();
  bool full();

  //private:
  size_type capacity_;
  size_type front_;
  size_type size_;
  pointer buffer_;
};

void swap(Queue& lhs, Queue& rhs);
// declare necessary non-member function(s) ...

}
#endif
