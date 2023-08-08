/*!*****************************************************************************
\file bitset.hpp
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 1
\date 18/09/2021

\brief
This program implements a class template bitset representing 
a fixed-size sequence of N bits (number of bits to be allocated).
Bitset manipulates standard logic operators such as 
OR(|), AND(&) and XOR(^) operations. 
It includes functions that converts the contents to strings.

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
namespace csd2125
{
    /**************************************************************************/
    /*! 
    \brief
        Allocates memory for N bit size and sets all bits to false(0)
    */
    /**************************************************************************/
    template <size_t N>
    constexpr bitset<N>::bitset() noexcept
    {
        //  1 byte  = 8 bits 
        //  e.g char   = 1 byte  = 8 bits
        //      int    = 4 bytes = 32 bits
        //      size_t = 8 bytes = 64 bits

        //  CHAR_BIT = 8 bits
        //  N just represents the number of bits the user inputs
        size_t byte_size =  N / CHAR_BIT;


        //  N % CHAR_BIT == 0, if true means that if the length of bitset is  
        //  divisable by 8 with no remainders, that amount of bytes (N / CHAR_BIT) 
        //  will be allocated. 
        //  However, if false and there are remainders 1 extra byte ((N / CHAR_BIT) + 1)
        //  will be allocted to store the overflow.
        if (N % CHAR_BIT == 0)
        {
            data = new char[byte_size];
        }
        else
        {
            byte_size += 1;
            data = new char [byte_size];
        }
    }

    /**************************************************************************/
    /*! 
    \brief
        Deletes the memory of bits.
        Gets destructor when program ends.
    */
    /**************************************************************************/
    template <size_t N>
    bitset<N>::~bitset()
    {
        delete[] data;
    }

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
    template <size_t N>
    void bitset<N>::set(size_t pos, bool val)
    {
        if (pos > N-1)
        {
            throw std::out_of_range 
            {
                "Pos out of range"
            };
        }
        
        if (val == true)
            data[pos/CHAR_BIT] |= static_cast<char>(1 << (pos % CHAR_BIT));
        else
            data[pos / CHAR_BIT] &= static_cast<char>(~(1 << (pos % CHAR_BIT)));
    }


    /**************************************************************************/
    /*! 
    \brief
        Clear bit at position pos by setting its value to false

    \param pos
        Position of the bit to reset to 0
    */
    /**************************************************************************/
    template <size_t N>
    void bitset<N>::reset(size_t pos)
    {
        if (pos > N-1)
        {
            throw std::out_of_range 
            {
                "Pos out of range"
            };
        }

        data[pos / CHAR_BIT] &= false;
    }

    /**************************************************************************/
    /*! 
    \brief
        Flip bit value at position pos.
        Changes the true values to false and false values to true.

    \param pos
        Position of the bit to flip 
    */
    /**************************************************************************/
    template <size_t N>
    void bitset<N>::flip(size_t pos)
    {
        if (pos > N-1)
        {
            throw std::out_of_range 
            {
                "Pos out of range"
            };
        }

        if (data[pos/CHAR_BIT])
            data[pos / CHAR_BIT] &= static_cast<char>(~(1 << ((pos % CHAR_BIT))));
        else
            data[pos / CHAR_BIT] |= static_cast<char>(1 << ((pos % CHAR_BIT)));
    }

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
    template <size_t N>
    bool bitset<N>::test(size_t pos) const
    {
        if (pos > N-1)
        {
            throw std::out_of_range 
            {
                "Pos out of range"
            };
        }
        
        return data[pos/CHAR_BIT] & (1 << (pos % CHAR_BIT));
    }

    /**************************************************************************/
    /*! 
    \brief
        Returns the number of bits allocated as N.

    \return 
        Returns the number of bits allocated as N.
    */
    /**************************************************************************/
    template <size_t N>
    size_t bitset<N>::size() const
    {
        return N;
    }

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
    template <size_t N>
    bool bitset<N>::operator[] (const size_t &pos) 
    {
        if (pos > N-1)
        {
            throw std::out_of_range 
            {
                "Pos out of range"
            };
        }

        return data[pos / CHAR_BIT] & (1 << (pos % CHAR_BIT));
    }

    /**************************************************************************/
    /*! 
    \brief
        Counts the number of bits that are set to true, 1
        eg. 0000 1111 returns 4 1s in size_t

    \return 
         The number of bits set in the bit sequence.
    */
    /**************************************************************************/
    template <size_t N>
    size_t bitset<N>::count() const
    {
        size_t counter {0};
        for(size_t i = 0; i < N; i++)
        {
            if(data[i / CHAR_BIT] & (1 << (i % CHAR_BIT)))
            {
                counter++;
            }
        }
        return counter;
    }

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
    template <size_t N>
    std::string bitset<N>::to_string(char _0, char _1) const
    { 
        //  So you’re creating a string filled with the zeros first,
        //  then looping through your data,
        //  if the bit is true replace it in the string with your ones
#if 0
        std::string str (N, _0);
#else
        std::string str;
        str.resize(N);

        for(size_t i = 0; i < str.length(); i++)
        {
            str[i] = _0;
        }
#endif
        size_t counter = N - 1;

        for (size_t i = 0; i < N; i++)
        {
            if (data [counter / CHAR_BIT] & (1 << (i % CHAR_BIT)))
            {
                str[counter] = _1;
            }
            
            counter--;
        }

        return str;
    }

}