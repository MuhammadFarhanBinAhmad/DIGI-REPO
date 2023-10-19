// Provide file documentation header
// Don't include any C and C++ standard library headers!!!
// Remember, this file is incomplete and you must provide missing details/features.

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream> // std::ostream

namespace HLP3 {
template<typename T,size_t N>
class Polynomial
{
    public:
    Polynomial() = default;
    Polynomial(const &Polynomial rhs);
    
    Polynomial& operator*();
    T operator[](int index) const;
    T& operator[](int index);
    Polynomial& operator=(const &Polynomial rhs);


    private:
    T coefficients[N+1];

}
// declare class template Polynomial

}

#include "polynomial.tpp"

#endif
