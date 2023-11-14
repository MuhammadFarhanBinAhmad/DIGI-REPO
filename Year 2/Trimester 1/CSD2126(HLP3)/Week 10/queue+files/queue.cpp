/*!************************************************************************
\file queue.cpp
\author Tan Jun Rong
\par DP email: t.junrong\@digipen.edu
\par Course: CSD 2126
\par Assignment 6
\date 04-11-2023

\brief
This source file implements functions for a circular buffer queue class.
**************************************************************************/

#include "queue.hpp"

namespace HLP3 {

    /*!***********************************************************************
    \brief
        Constructor
    *************************************************************************/
    Queue::Queue(size_type queueSize) {
        base = new value_type[queueSize];
        queueCapacity = queueSize;
        count = 0;
        firstIndex = 0;
    }

    /*!***********************************************************************
    \brief
        Destructor
    *************************************************************************/
    Queue::~Queue() {
        delete[] base;
    }

    /*!***********************************************************************
    \brief
        Copy constructor.
    *************************************************************************/
    Queue::Queue(const Queue& other) {
        // Allocate memory.
        base = new value_type[other.queueCapacity];
        // Copy values.
        queueCapacity = other.queueCapacity;
        count = other.count;
        firstIndex = other.firstIndex;
        // Copy queue values.
        for (size_type i = 0; i < queueCapacity; ++i) {
            base[i] = other.base[i];
        }
    }

    /*!***********************************************************************
    \brief
        Copy assignment constructor.
    *************************************************************************/
    Queue& Queue::operator=(Queue const& other) {
        // Copy swap idiom.
        Queue temp(other);
        swap(temp);
        return *this;
    }

    /*!***********************************************************************
    \brief
        Get read only queue.
    *************************************************************************/
    Queue::pointer Queue::c_buff() const {
        return base;
    }

    /*!***********************************************************************
    \brief
        Check if queue is empty.
    *************************************************************************/
    bool Queue::empty() {
        return (count) ? false : true;
    }

    /*!***********************************************************************
    \brief
        Check if queue is full.
    *************************************************************************/
    bool Queue::full() {
        return (count == capacity()) ? true : false;
    }

    /*!***********************************************************************
    \brief
        Get queue size.
    *************************************************************************/
    Queue::size_type Queue::size() const {
        return count;
    }

    /*!***********************************************************************
    \brief
        Get queue max size.
    *************************************************************************/
    Queue::size_type Queue::capacity() const {
        return queueCapacity;
    }

    /*!***********************************************************************
    \brief
        Push values in queue.
    *************************************************************************/
    void Queue::push(value_type val) {
        // Get index to insert value.
        size_type tail = (firstIndex + count) % queueCapacity;
        base[tail] = val;

        ++count;

        if (count > queueCapacity) {
            // Increment the index to start from.
            ++firstIndex;
            // Prevent count from going over the max cap.
            count = queueCapacity;
        }

        // Loop first index back to 0.
        if (firstIndex >= queueCapacity) firstIndex = 0;
    }

    /*!***********************************************************************
    \brief
        Pop oldest value from queue.
    *************************************************************************/
    void Queue::pop() {
        // Increment the index to start from.
        ++firstIndex;

        // Decrease amount of values in queue.
        if (count > 0) { --count; }

        // Loop first index back to 0.
        if (firstIndex >= queueCapacity) firstIndex = 0;
    }

    /*!***********************************************************************
    \brief
        Get first index value of the queue.
    *************************************************************************/
    Queue::reference Queue::front() {
        return *(base + firstIndex);
    }

    /*!***********************************************************************
    \brief
        Get first index value of the queue.
    *************************************************************************/
    Queue::const_reference Queue::front() const {
        return *(base + firstIndex);
    }

    /*!***********************************************************************
    \brief
        Get last index value of the queue.
    *************************************************************************/
    Queue::reference Queue::back() {
        size_type tail = (firstIndex + count - 1) % queueCapacity;
        return *(base + tail);
    }

    /*!***********************************************************************
    \brief
        Get last index value of the queue.
    *************************************************************************/
    Queue::const_reference Queue::back() const {
        size_type tail = (firstIndex + count - 1) % queueCapacity;
        return *(base + tail);
    }

    /*!***********************************************************************
    \brief
        Get first index of queue.
    *************************************************************************/
    Queue::size_type Queue::front_index() const {
        return firstIndex;
    }

    /*!***********************************************************************
    \brief
        Get last index of queue.
    *************************************************************************/
    Queue::size_type Queue::back_index() const {
        size_type tail = (firstIndex + count) % queueCapacity;
        return tail;
    }

    /*!***********************************************************************
    \brief
        Swap this queue with another.
    *************************************************************************/
    void Queue::swap(Queue& other) {
        // Swap pointer.
        value_type* temp_base = base;
        base = other.base;
        other.base = temp_base;

        // Swap data.
        size_type temp_size = queueCapacity;
        queueCapacity = other.queueCapacity;
        other.queueCapacity = temp_size;

        size_type temp_count = count;
        count = other.count;
        other.count = temp_count;

        size_type temp_front_index = firstIndex;
        firstIndex = other.firstIndex;
        other.firstIndex = temp_front_index;
    }

    /*!***********************************************************************
    \brief
        Swap two queues.
    *************************************************************************/
    void swap(Queue& lhs, Queue& rhs) {
        // Swap pointer.
        Queue::value_type* temp_base = lhs.base;
        lhs.base = rhs.base;
        rhs.base = temp_base;

        // Swap data.
        Queue::size_type temp_size = lhs.queueCapacity;
        lhs.queueCapacity = rhs.queueCapacity;
        rhs.queueCapacity = temp_size;

        Queue::size_type temp_count = lhs.count;
        lhs.count = rhs.count;
        rhs.count = temp_count;

        Queue::size_type temp_front_index = lhs.firstIndex;
        lhs.firstIndex = rhs.firstIndex;
        rhs.firstIndex = temp_front_index;
    }
}
