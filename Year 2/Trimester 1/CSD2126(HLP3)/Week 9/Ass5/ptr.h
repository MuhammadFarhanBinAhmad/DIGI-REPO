
/*****************************************************************/ /**
  * \file	ptr.h
  * \brief	Your task is to extend this partially defined class template Ptr with six (6) member functions
            that will enable the unit tests in driver source file ptr-driver.cpp to successfully compile and
            link to generate an executable file that will then generate the correct output for each unit test.

            Carefully read the unit tests in driver source file ptr-driver.cpp to determine the member functions that
            you must declare and define for class template Ptr.
            The driver source file contains the expected output and provides hints to the member functions that you
            must implement to successfully complete the puzzle.

            If you don't implement the required functions [again there are six such functions], it is possible to
            obtain the same results as described in the driver. However, in such cases, the online grader will
            reject your submission.

            You can define the member functions inline or outside the class template definition!!!
  *
  * \author	 FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
  *
  * \note    I like this assigment, feel like something i will do during the "holiday" as revision
  *          just minus making the driver
  *
  * \date	29-OCT-2023
 ***********************************************************************/
// TODO: Provide file documentation header

// TODO: Don't include any other C and C++ standard library headers!!!

#include <iostream> // std::ostream

#ifndef PTR_H
#define PTR_H

namespace HLP3
{

  // partially defined class template Ptr
  template <typename T>
  class Ptr
  {
  private:
    T *p; // DO NOT AMEND!!!
  public:
    Ptr() = delete;                  // DO NOT AMEND!!!
    Ptr(Ptr &&) = delete;            // DO NOT AMEND!!!
    Ptr &operator=(Ptr &&) = delete; // DO NOT AMEND!!!
    explicit Ptr(T *_p) : p{_p} {}   // DO NOT AMEND!!!
    ~Ptr()
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
      delete p;
    } // DO NOT AMEND!!!

    T *get() const { return p; } // DO NOT AMEND!!!b

    //Copy constructor
    Ptr(const Ptr &other) : p(new T(*(other.p))) {}

    //Assignment *operator
    T& operator*(){return *p;}

    //= operator
    Ptr& operator=(const Ptr &other)
    {
      if (this != &other) 
      {
        delete p; // Need delete or else kena double deletion error
        p = new T(*(other.p)); // Need make deep copy
      }
      return *this;
    }

    //conversion constructor
    //static_cast<>??. Impleciat conversion. Simple type can but what if other type??
    template<typename OtherType>
    Ptr(const Ptr<OtherType> &other):  p(new T(*(other.get()))){}

    //conversion =operator
    template<typename OtherType>
    Ptr& operator=(const Ptr<OtherType> &other)
    {
      //Different type so really no need to check.
      //if (this != &other)
      {
        delete p;
        p = new T(*(other.get()));
      }
      return *this;
    }

    //That simple ah? I spend 5 min overthinking this
    //->operator
    T* operator->()
    {
      return p;
    }
  };
} // end namespace HLP3

#endif // #ifndef PTR_H
