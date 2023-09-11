
#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>

namespace HLP3
{
    template<size_t N> class bitset
    {
    private:
        char *data;
    public:
        //noexcept: Perform compile-time check that returns true if
        //          an expression is declared to no throw any exceptions
        constexpr bitset() noexcept;
        ~bitset();

        bool operator[](const size_t &pos);

        void set(size_t pos, bool val = true);
        void reset(size_t pos);
        void flip(size_t pos);
        bool test(size_t pos) const;
        size_t size() const;
        size_t count() const;
        std::string to_string(char _0 = '0' , char _1 = '1') const;
    };
}

#include "bitset.hpp"