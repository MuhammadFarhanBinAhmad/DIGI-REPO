/*****************************************************************/ /**
  * \file	queue.cpp
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

#include "queue.hpp"

namespace HLP3
{

  Queue::Queue(Queue::size_type size)
  {
    
    buffer_ = new value_type[size];
    capacity_ = size;
    front_ = 0;
    size_ = 0;
  }

  Queue::Queue(const Queue &rhs)
  {
    buffer_ = new value_type[rhs.capacity_];
    capacity_ = rhs.capacity_;
    front_ = rhs.front_;
    size_ = rhs.size_;

    for (size_type i = 0; i < rhs.capacity_; ++i)
    {
      buffer_[i] = rhs.buffer_[i];
    }
  }

  Queue::~Queue()
  {
    delete[] buffer_;
  }

  Queue &Queue::operator=(const Queue &rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }

    Queue temp(rhs);
    swap(temp);
    return *this;
  }

  void Queue::push(value_type value)
  {
    // // if buffer not full
    // if (size_ < capacity_)
    // {
    //   buffer_[(front_ + size_) % capacity_] = value;
    //   size_++;
    // }
    // // if buffer is full
    // else
    // {
    //   // remove the oldest member to make way for the new value
    //   front_ = (front_ + 1) % capacity_;
    //   buffer_[(front_ + size_ - 1) % capacity_] = value;
    // }
    // Get index to insert value.
    size_type tail = (front_ + size_) % capacity_;
    buffer_[tail] = value;

    ++size_;

    if (size_ > capacity_)
    {
      // Increment the index to start from.
      front_++;
      // Prevent count from going over the max cap.
      size_ = capacity_;
    }

    // Loop first index back to 0.
    if (front_ >= capacity_)
      front_ = 0;
  }
  void Queue::pop()
  {
    if (size_ == 0)
    {
      // I know breif say user is responsible. But i got trust issue
      return;
    }
    front_ = (front_ + 1) % capacity_;
    size_--;
  }

  void Queue::swap(Queue &rhs)
  {
    size_type temp_capacity = rhs.capacity_;
    size_type temp_front = rhs.front_;
    size_type temp_size = rhs.size_;
    pointer temp_buffer = rhs.buffer_;

    rhs.capacity_ = capacity_;
    rhs.front_ = front_;
    rhs.size_ = size_;
    rhs.buffer_ = buffer_;

    capacity_ = temp_capacity;
    front_ = temp_front;
    size_ = temp_size;
    buffer_ = temp_buffer;
  }

  void swap(Queue &lhs, Queue &rhs)
  {
    // Queue::pointer temp_buffer_ = lhs.buffer_;
    // lhs.buffer_ = rhs.buffer_;
    // rhs.buffer_ = temp_buffer_;
    // // Swap data.
    // Queue::size_type temp_capacity_ = lhs.capacity_;
    // lhs.capacity_ = rhs.capacity_;
    // rhs.capacity_ = temp_capacity_;
    // Queue::size_type temp_size = lhs.size_;
    // lhs.size_ = rhs.size_;
    // rhs.size_ = temp_size;
    // Queue::size_type temp_front = lhs.front_;
    // lhs.front_ = rhs.front_;
    // rhs.front_ = temp_front;
    
    lhs.swap(rhs);
  }

  Queue::reference Queue::front()
  {
    if (empty())
    {
      return buffer_[0];
    }
    return buffer_[front_];
  }


  Queue::const_reference Queue::front() const
  {
    if (empty())
    {
      return buffer_[0];
    }
    return buffer_[front_];
  }
  
  Queue::reference Queue::back()
  {
    if (empty())
    {
      return buffer_[0];
    }
    return buffer_[(front_ + size_ - 1) % capacity_];
  }

  Queue::const_reference Queue::back() const
  {
    if (empty())
    {
      return buffer_[0];
    }
    return buffer_[(front_ + size_ - 1) % capacity_];
  }

  Queue::size_type Queue::front_index() const { return front_; }
  Queue::size_type Queue::back_index() const { return (front_ + size_) % capacity_; }
  Queue::size_type Queue::capacity() const { return capacity_; }
  Queue::size_type Queue::size() const { return size_; }
  Queue::pointer Queue::c_buff() const { return buffer_; }
  
  bool Queue::empty() const { return size_ == 0 ? true : false; }
  bool Queue::empty()  { return size_ == 0 ? true : false; }
  bool Queue::full() const { return size_ == capacity_ ? true : false; }
  bool Queue::full()  { return size_ == capacity_ ? true : false; }

}
