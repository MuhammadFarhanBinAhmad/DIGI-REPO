/*!*****************************************************************************
\file allocator.hpp
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 4
\date 12/11/2021

\brief
This is a custom library for allocation and deallocation of bytes.

void *operator new(size_t)
  - Operator new overloading.

void operator delete(void*)
  - Operator delete overloading.

void operator delete(void*, size_t)
  - A memory allocator can use the given size to be more efficient.
    Identical to operator delete(void*)

pointer allocate(size_t)
  - Allocates n * sizeof(T) bytes of uninitialized storage
    by calling ::operator new(size_t)

void deallocate(pointer, size_t)
  - Deallocates the storage referenced by the pointer p, 
    which must be a pointer obtained by an earlier call to allocate().

*******************************************************************************/

#include <forward_list>

// TODO: Define your own global operators.
// https://en.cppreference.com/w/cpp/memory/new/operator_new

/*!*****************************************************************************
    \brief
    Operator new overloading.
    Called by non-array new-expressions to allocate storage required for a
    single object. This custom library implementation allocates count bytes
    from free store.
    \param sz
    number of bytes to allocate
*******************************************************************************/
void *operator new(size_t sz) 
{
  void *m = std::malloc(sz);
  std::cout << "  Global allocate " << sz << " bytes." << std::endl;
  return m;
}

/*!*****************************************************************************
    \brief
    Operator delete overloading.
    Called by delete-expressions to deallocate storage previously allocated
    for a single object. The behavior of this custom library implementation
    of this function is undefined unless ptr is a null pointer or is a pointer
    previously obtained from this custom library implementation of operator
    new(size_t)
    \param m
    pointer to a memory block to deallocate or a null pointer
*******************************************************************************/
void operator delete(void *m) 
{
  std::free(m);
  std::cout << "  Global deallocate." << std::endl;
}

/*!*****************************************************************************
    \brief
    Operator delete overloading.
    A memory allocator can use the given size to be more efficient.
    This custom library implementation is identical to operator delete(void*).
    \param m
    pointer to a memory block to deallocate or a null pointer
    \param sz
    the size that was passed to the matching allocation function
*******************************************************************************/
void operator delete(void* m, size_t sz)
{
  std::cout << "  Global deallocate" << sz << " bytes." << std::endl;
  ::operator delete(m);
}

namespace csd2125 
{

template <typename TDataType, typename TFlags> //example <vertex, short>
class allocator 
{
  // TODO: Define your own allocator class.
  private:
    struct pool
    {
      // bit mask
      TFlags flags; 
      // array of TDataType objects
      // bytes * 8 = number of bits
      TDataType elements[sizeof(TFlags)*8]; 
    };
    std::forward_list<pool> pools;

  public:
    struct pointer 
    {
      pool *p;
      size_t i;  // starting index
    };

    /*!*****************************************************************************
      \brief
      Allocates n * sizeof(T) bytes of uninitialized storage
      by calling ::operator new(size_t).
      \param count
      the number of objects to allocate storage for
      \return
      Pointer to struct pool and a starting index.
    *******************************************************************************/
    pointer allocate(size_t count) 
    {
      std::cout << std::endl << "  Allocator allocate " << count << " elements. " << std::endl;

      // count is greater than the maximum number of elements allowed in a single pool

      //whats the number of a single pool?

      if (count > sizeof(TFlags)*8) 
      {
        throw std::bad_alloc();
      }

      pointer ptr{};
      bool found = false; // flag to indicate if a compatible pool has been found
      TFlags idx = 0;

      // find the first compatible pool
      for (auto &p : pools) 
      {
        TFlags length = 0;
        idx = 0;

        // check if pool is compatible
        for (TFlags i = 0; (size_t)i < sizeof(TFlags)*8; ++i) 
        {
          // is i_th bit set?
          if ((p.flags >> i) & 1) 
          {
            length = 0;
          } else 
          {
            // count continuous bit not set?
            if ((size_t)++length == count) 
            {
              found = true;
              idx = i - length + 1;
              break;
            }
          }
        }

        // has a compatible pool been found?
        if (found) 
        {
          // update flags
          TFlags flags = ((1 << count) - 1) << idx;
          p.flags = p.flags | flags;
          // update elements
          for (TFlags i = idx; (size_t) i < idx+count; ++i) 
          {
            p.elements[i] = TDataType();
          }

          // update pointer
          ptr.p = &p;
          ptr.i = idx;
          break;
        }

        std::cout << "  Did not find space in a pool." << std::endl;
        std::cout << "  Checking next available pool..." << std::endl;
      }

      // no compatible pool found; add a new pool
      if (!found) 
      {
        std::cout << "  Allocating a new pool." << std::endl;
        pool p{};
        idx = 0;
        p.flags = ((1 << count) - 1);
        for (TFlags i = 0; (size_t) i < count; ++i) 
        {
          p.elements[i] = TDataType();
        }
        pools.push_front(p);

        ptr.p = &(pools.front());
        ptr.i = idx;
      }

      std::cout << "  Found space in a pool for " << count << " elements at index " << idx << "." << std::endl;
      return ptr;
    }

    /*!*****************************************************************************
      \brief
      Deallocates the storage referenced by the pointer p, 
      which must be a pointer obtained by an earlier call to allocate().
      \param ptr
      pointer obtained from allocate()
      \param count
      number of objects earlier passed to allocate()
    *******************************************************************************/
    void deallocate(pointer ptr, size_t count) 
    {
      std::cout << "  Allocator deallocate " << count << " elements. " << std::endl;

      auto it = pools.before_begin();
      for (auto &p : pools) 
      {
        // found the pool?
        if (ptr.p == &p) 
        {
          std::cout << "  Found " << count << " elements in a pool." << std::endl;

          // update flags
          TFlags flags = ((1 << count) - 1) << ptr.i;
          p.flags = p.flags & (~flags);
          // no elements used in a memory pool after deallocation
          if (p.flags == 0) 
          {
            std::cout << "  Removing an empty pool." << std::endl;
            // remove the pool from the list
            pools.erase_after(it);
          }

          return;
        }

        std::cout << "  Checking next existing pool..." << std::endl;
        ++it;
      }

      // deallocate memory at an address that does not belong to any of the pool
      throw std::bad_alloc();
    }
};

struct vector {
  float x, y, z, w; // 4 floats

  // https://en.cppreference.com/w/cpp/language/constructor
  // constructor definition. ": x{0}, y{0}, z{0}, w{0}" is the initialiser list.
  vector() : x{0}, y{0}, z{0}, w{0} {}  // constructor 1: initialise the 4 floats to 0
  vector(float ax, float ay, float az, float aw) : x{ax}, y{ay}, z{az}, w{aw} {}  // constructor 2: takes in 4 arguments and assign to the 4 floats

  // TODO: Define your own in-class operators.

  /*!*****************************************************************************
      \brief
      Operator new overloading belonging to vector struct.
      Takes in the global operator new that has been defined previously.
      \param sz
      number of bytes to allocate
  *******************************************************************************/
  void* operator new(size_t sz) 
  {
    std::cout << "  In-class allocate " << sz << " bytes." << std::endl;
    void *m = ::operator new(sz);
    return m;
  }

  /*!*****************************************************************************
      \brief
      Operator new overloading belonging to vector struct.
      Takes in the global operator delete that has been defined previously.
      \param m
      pointer to a memory block to deallocate or a null pointer
  *******************************************************************************/
  void operator delete(void *m) 
  {
    std::cout << "  In-class deallocate." << std::endl;
    ::operator delete(m);
  }
}; // end struct vector

union vertex {
  vector vertexCoordinates; // a vector
  float axisCoordinates[sizeof(vector) / sizeof(float)];  // an array of 4 floats

  vertex() : vertexCoordinates{} {} // constructor 1: calls constructor 1 of vector
  vertex(float ax, float ay, float az, float aw) : vertexCoordinates{ax, ay, az, aw} { }  // constructor 2: calls constructor 2 of vector
}; // end union vertex

} // end namespace