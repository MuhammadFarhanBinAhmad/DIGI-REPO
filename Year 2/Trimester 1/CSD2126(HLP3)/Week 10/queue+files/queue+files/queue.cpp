#include "queue.hpp"
// don't include any other headers files [otherwise, the online grader will
// not accept your submission ...]

namespace HLP3
{

  Queue::Queue(Queue::size_type size)
  {
    capacity_ = size;
    front_ = 0;
    size_ = 0;
    buffer_ = new value_type[capacity_];
  }

  Queue::Queue(const Queue &rhs)
  {
    capacity_ = rhs.capacity_;
    front_ = rhs.front_;
    size_ = rhs.size_;
    buffer_ = new value_type[rhs.capacity_];

    for (size_type i = 0; i < rhs.size_; ++i)
    {
      buffer_[(front_ + i) % capacity_] = rhs.buffer_[(rhs.front_ + i) % rhs.capacity_];
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
    // if buffer not full
    if (size_ < capacity_)
    {
      buffer_[(front_ + size_) % capacity_] = value;
      size_++;
    }
    // if buffer is full
    else
    {
      // remove the oldest member to make way for the new value
      front_ = (front_ + 1) % capacity_;
      buffer_[(front_ + size_ - 1) % capacity_] = value;
    }
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
  Queue::reference Queue::back()
  {
    if (empty())
    {
      return buffer_[0];
    }
    return buffer_[(front_ + size_ - 1) % capacity_];
  }

  Queue::size_type Queue::front_index() const { return front_; }
  Queue::size_type Queue::back_index() const { return ((front_index() + size()) % 4); }
  Queue::size_type Queue::capacity() const { return capacity_; }
  Queue::size_type Queue::size() const { return size_; }
  Queue::pointer Queue::c_buff() const { return buffer_; }
  bool Queue::empty() const { return size_ == 0 ? true : false; }
  bool Queue::full() const { return size_ == capacity_ ? true : false; }

}
