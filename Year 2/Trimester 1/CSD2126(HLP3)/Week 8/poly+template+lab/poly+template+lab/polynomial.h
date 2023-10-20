/*****************************************************************/ /*
* \file	polynomial.hpp
  * \brief	This assignment will provide you with the knowledge and practice required to develop and
            implement software involving:
            1. Design and implementation of class templates.
            2. Ability to understand and implement mathematical concepts in C++.
  *
  * \author	FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
  *
  * \note    I thought i know template. I was wrong. Need to think of more crazy
  *          way to play with template.
  *
  * \date	20-OCT-2023
 ***********************************************************************/
// Provide file documentation header
// Don't include any C and C++ standard library headers!!!
// Remember, this file is incomplete and you must provide missing details/features.

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream> // std::ostream

namespace HLP3 
{
template<typename CoefficientType,int Degree>
class Polynomial
{
    public:
    //Constructor
    Polynomial();
    //Special argument constructor
    Polynomial(const Polynomial& rhs);

    // Declare non-modifiable operator[]
    CoefficientType operator[](int index) const;

    // Declare modifiable operator[]
    CoefficientType& operator[](int index);

    //I didnt know this thing work. more you know huh
    //operator()
    template <typename DestinationCoefficientType, int DestinationDegree>
    operator Polynomial<DestinationCoefficientType, DestinationDegree>() const
    {
    HLP3::Polynomial<DestinationCoefficientType, DestinationDegree> result;

    for (int i = 0; i <= Degree && i <= DestinationDegree; ++i) {
        result[i] = static_cast<DestinationCoefficientType>(coefficients[i]);
    }

    return result;
    }


    //Declare copy assigment
    Polynomial<CoefficientType,Degree>& operator=(const Polynomial<CoefficientType,Degree>& rhs);

    //operatot()
    CoefficientType operator()(CoefficientType rhs) const;

    private:
    CoefficientType coefficients[Degree+1];
};

//non-member *operator function
template <typename CoefficientType, int Degree1, int Degree2>
    Polynomial<CoefficientType, Degree1 + Degree2> operator*(const Polynomial<CoefficientType, Degree1>& lhs,const Polynomial<CoefficientType, Degree2>& rhs);

}

#include "polynomial.tpp"

#endif
