

// REMINDER -
// 0 - FALSE
// 1 - TRUE
namespace HLP3
{
    /*!
    \brief Need allocate memory of N bit size. Also need to set all the bits to false(0)
    */
    template <size_t N>
    constexpr bitset<N>::bitset() noexcept
    {
        size_t Byte_Size = N/ CHAR_BIT;

        if (N % CHAR_BIT == 0)
        {
            data = new char [Byte_Size];
        }
        else
        {
            Byte_Size++;
            data = new char [Byte_Size];
        }
    }
    /*!
    \brief Delete bits of memory
    */
    template <size_t N>
    bitset<N>::~bitset()
    {
        delete[] data;
    }
    /*!
    \brief Use to access the bit at a specific position

    \param pos
        The position of the bit you wish to access
    */
    template <size_t N>
    bool bitset<N>::operator[](const size_t &pos)
    {
        if (pos > N -1)
        {
            throw std::out_of_range
            {
                "Pos out of range"
            };
        }

        return data[pos/CHAR_BIT] & (1 << (pos % CHAR_BIT));
    }
    /*!
    \brief Set bit that's at position pos to value

    \param pos
        Set position of the bit to set
    \param val
        Value to the set the bit to
    */
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
        {
            data[pos/CHAR_BIT] |= static_cast<char>(1 << (pos % CHAR_BIT));
        }
        else
        {
            data[pos/CHAR_BIT] &= static_cast<char>(~(1 << (pos % CHAR_BIT)));
        }

    }
    /*!
    \brief Clear the bit the a desire position(pos) by setting it to false(0)

    \param pos
        Position of the bit you wish to reset 
    */
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

        data[pos/CHAR_BIT] &= false;
    }
    /*!
    \brief Flip a desired bit value

    \param pos
        Position of the bit you wish to flip
    */
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
        {
            data[pos/CHAR_BIT] &= static_cast<char>(~(1 << ((pos % CHAR_BIT))));
        }
        else
        {
            data[pos/CHAR_BIT] |= static_cast<char>(1 << ((pos % CHAR_BIT)));
        }
    }
    /*!
    \brief  Use to test if whether the bit at a specific position in a bitset is set to 1
            The member function throws a out_of_range if size() <= pos.
            Else, it will return true if only the bit at the set postion is set

    \param pos
        Position of the bit to test
    \param val
        Value to the set the bit to
    \return Return the value of the bit at the specified position
    */
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

        return data[pos/CHAR_BIT] & (1 << (pos% CHAR_BIT));
    }
    /*!
    \brief Return the number of bits that's allocated

    \return
        Return the number of bits that's allocated
    */
    template <size_t N>
    size_t bitset<N>::size() const
    {
        return N;
    }
    /*!
    \brief  Count the number of bits that are set to true(1)
            eg. 0010 1101 - return 4 cause 4 1s is present

    \return Return the total amount of 1 bits present
    */
    template <size_t N>
    size_t bitset<N>::count() const
    {
        size_t counter = 0;
        for (size_t i = 0; i < N; i++)
        {
            if (data[i/CHAR_BIT] & (1 << (i % CHAR_BIT)))
            {
                counter++;
            }
        }
        return counter;
    }
    /*!
    \brief Set bit that's at position pos to value

    \param pos
        Set position of the bit to set
    \param val
        Value to the set the bit to
    */
    template <size_t N>
    std::string bitset<N>::to_string(char _0, char _1) const
    {
        #if 0
        std::string str (N,_0);
        #else
        std::string str{};
        str.resize(N);

        for (size_t i = 0 ; i < str.length();i++)
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