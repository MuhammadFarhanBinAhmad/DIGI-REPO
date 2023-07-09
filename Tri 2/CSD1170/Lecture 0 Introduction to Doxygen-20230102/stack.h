/******************************************************************************/
/*!
\file   stack.h
\author Artie Fufkin
\par    email: cooldude234\@hotmail.com
\par    DigiPen login: afufkin
\par    Course: CS170
\par    Section C
\par    Assignment #1
\date   7/20/2021
\brief  
  This is the interface file for all member functions
  of a class called Stack.  
  
*/
/******************************************************************************/


/******************************************************************************/
/*!
  \class Stack
  \brief  
    The stack class implements a Last-In-First-Out (LIFO) data
    structure for storing/retrieving integers.

    Operations include:

    - Add an item to the stack
    - Remove an item from the stack
    - Read item on top of the stack
    - Check to see if the stack is empty
    - Check to see if the stack is full
    - Output the stack to a stream
    - Return the number of items on the stack
    - Return the size of the stack

  \deprecated 
    The <b>isEmpty</b> method should be used in place of the <b>isNotFull</b> 
    method.

  \bug  
    Pushing the number 42 onto the stack causes a segmentation fault.
  \bug
    Popping the number 11 causes day to become night. (Maybe that's a feature?)
*/
/******************************************************************************/

#include <ostream>

//! Maximum size of a stack 
const int MAX_SIZE = 10;

class Stack {
public:
  Stack();
  Stack(int initial_size);
  void pushItem(int item);
  int popItem(void);
  int peekAtTop(void) const;
  bool isEmpty(void) const;
  bool isFull(void) const;
  void print(void) const;
  void print(std::ostream &stream, int width) const;
  int getCount(void) const;
  int getSize(void) const;
private:
    //! The index of the top of the stack
  int top;             
    //! The current size of the stack     
  int size;            
    //! The array of integers (stack)
  int items[MAX_SIZE]; 
};
