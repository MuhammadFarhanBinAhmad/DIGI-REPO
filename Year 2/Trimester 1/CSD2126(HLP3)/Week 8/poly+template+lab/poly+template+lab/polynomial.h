// Provide file documentation header
// Don't include any C and C++ standard library headers!!!
// Remember, this file is incomplete and you must provide missing details/features.

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream> // std::ostream
#include <vector>

namespace HLP3 
{
template<typename CoefficientType,int Degree>
class Polynomial
{
    public:
    Polynomial();
    Polynomial(const Polynomial& rhs);

    // Declare non-modifiable operator[]
    CoefficientType operator[](int index) const;

    // Declare modifiable operator[]
    CoefficientType& operator[](int index);

    //Declare operator*
    Polynomial<CoefficientType,Degree> operator*(const Polynomial<CoefficientType,Degree>& rhs) const;

    template <typename OtherType>
    Polynomial<OtherType, Degree> operator*(const Polynomial<CoefficientType, Degree>& rhs) const;

    //Declare copy assigment
    Polynomial<CoefficientType,Degree>& operator=(const Polynomial<CoefficientType,Degree>& rhs);

    CoefficientType operator()(CoefficientType rhs) const;

    private:
    CoefficientType coefficients[Degree+1];
};

}

#include "polynomial.tpp"

#endif
