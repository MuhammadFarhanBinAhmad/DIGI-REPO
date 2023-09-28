/*!*****************************************************************************
\file bitset.h
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 1
\date 18/09/2021

\brief
This program contains the header of bitset.hpp.
It implements a class template bitset representing a fixed-size sequence 
of N bits (number of bits to be allocated).
Bitset manipulates standard logic operators 
such as OR(|), AND(&) and XOR(^) operations. 
It includes functions that converts the
contents to strings.

-Bitset constructor 
Allocates memory for N bits size

-~Bitset destructor
Deallocates memory 

-Set 
Set position of the bit to true or false (1 or 0)

-Reset
Set position of the bit to false(0)

-Flip
Changes the true values to false and false values to true using NOT operation
at the position of the bit

-Test 
Returns the value of the bit at the specific position specified

-Size
Returns the number of bits 

-operator[]
Access bit at specific position

-Count
Returns the number of bits set that are set to true

-to_string 
Returns a string representation of the data bits 

*******************************************************************************/
#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>

namespace csd2125
{
    // N: Size of the bitset, in terms of number of bits.
    template <size_t N> class bitset
    {
        private:
        char *data;

        public:

        /**************************************************************************/
        /*! 
        \brief
            Allocates memory for N bit size and sets all bits to false(0)
        */
        /**************************************************************************/
        constexpr bitset() noexcept;

        /**************************************************************************/
        /*! 
        \brief
            Deletes the memory of bits.
            Gets destructor when program ends.
        */
        /**************************************************************************/
        ~bitset();

        /**************************************************************************/
        /*! 
        \brief
            Set bit at position pos to value

        \param pos
            Position of the bit to set 
        
        \param value
            Value to set the bit
        */
        /**************************************************************************/
        void set(size_t pos, bool val = true);

        /**************************************************************************/
        /*! 
        \brief
            Clear bit at position pos by setting its value to false

        \param pos
            Position of the bit to reset to 0
        */
        /**************************************************************************/
        void reset(size_t pos);

        /**************************************************************************/
        /*! 
        \brief
            Flip bit value at position pos.
            Changes the true values to false and false values to true.

        \param pos
            Position of the bit to flip 
        */
        /**************************************************************************/
        void flip(size_t pos);

        /**************************************************************************/
        /*! 
        \brief
            Tests whether the bit at a specified position in a bitset is set to 1.
            The member function throws out_of_range if size() <= pos.
            Otherwise, it returns true only if the bit at position pos is set.

        \param pos
            Position of the bits to test

        \return 
            Returns the value of the bit at the position specified
        */
        /**************************************************************************/
        bool test(size_t pos) const;

        /**************************************************************************/
        /*! 
        \brief
            Returns the number of bits allocated as N.

        \return 
            Returns the number of bits allocated as N.
        */
        /**************************************************************************/
        size_t size() const;

        /**************************************************************************/
        /*! 
        \brief
            Access bit at specific position

        \param pos
            Position of the bit to access

        \return 
            Value of the bit in the position specified
        */
        /**************************************************************************/
        bool operator [] (const size_t &pos);

        /**************************************************************************/
        /*! 
        \brief
            Counts the number of bits that are set to true, 1
            eg. 0000 1111 returns 4 1s in size_t

        \return 
            The number of bits set in the bit sequence.
        */
        /**************************************************************************/
        size_t count() const;

        /**************************************************************************/
        /*! 
        \brief
            Displays the data bits as a string 

        \param _0
            A char to replace the 0 bits 

        \param _1
            A char to replace the 1 bits 

        \return 
            Converts a bitset object to a string representation.
            A string object where each bit set in the bitset has 
            a corresponding character of 1, and a character of 0 
            if the bit is unset.   
        */
        /**************************************************************************/
        std::string to_string(char _0 = '0', char _1 = '1') const;
    };

}

#include "bitset.hpp"
