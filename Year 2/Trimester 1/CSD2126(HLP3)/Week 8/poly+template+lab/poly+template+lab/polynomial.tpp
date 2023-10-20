/*****************************************************************/ /**
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

namespace HLP3
{
    // Define member functions of class template Polynomial ...
    template <typename CoefficientType, int Degree>
    Polynomial<CoefficientType, Degree>::Polynomial()
    {
        for (int i = 0; i <= Degree; ++i)
        {
            coefficients[i] = CoefficientType();
        }
    }

    template <typename CoefficientType, int Degree>
    Polynomial<CoefficientType, Degree>::Polynomial(const Polynomial &rhs)
    {
        for (int i = 0; i <= Degree; ++i)
        {
            coefficients[i] = rhs[i];
        }
    }

    // Define non-modifiable operator[] for reading coefficient values
    template <typename CoefficientType, int Degree>
    CoefficientType Polynomial<CoefficientType, Degree>::operator[](int index) const
    {
        if (index < 0 || index > Degree)
        {
            // std::cout <<"CATBUG";
            return CoefficientType();
        }
        return coefficients[index];
    }

    // Define modifiable operator[] for writing coefficient values
    template <typename CoefficientType, int Degree>
    CoefficientType &Polynomial<CoefficientType, Degree>::operator[](int index)
    {
        // need check degree
        if (index < 0 || index > Degree)
        {
            throw std::out_of_range("Index out of range");
        }
        return coefficients[index];
    }

    template <typename CoefficientType, int Degree1, int Degree2>
    Polynomial<CoefficientType, Degree1 + Degree2> operator*(const Polynomial<CoefficientType, Degree1> &lhs, const Polynomial<CoefficientType, Degree2> &rhs)
    {
        // combine both degree to create the new size polynomial
        Polynomial<CoefficientType, Degree1 + Degree2> result;

        for (int i = 0; i <= Degree1; ++i)
        {
            for (int j = 0; j <= Degree2; ++j)
            {
                result[i + j] += lhs[i] * rhs[j];
            }
        }

        return result;
    }

    template <typename CoefficientType, int Degree>
    Polynomial<CoefficientType, Degree> &Polynomial<CoefficientType, Degree>::operator=(const Polynomial<CoefficientType, Degree> &rhs)
    {
        for (int i = 0; i <= Degree; i++)
        {
            coefficients[i] = rhs[i];
        }
        return *this;
    }

    template <typename CoefficientType, int Degree>
    CoefficientType Polynomial<CoefficientType, Degree>::operator()(CoefficientType rhs) const
    {
        CoefficientType temp = coefficients[0]; // Initialize with the constant term

        // Calculate the polynomial value like this cause cant use std::pow
        for (int i = 1; i <= Degree; ++i)
        {
            CoefficientType term = 1;
            for (int j = 1; j <= i; ++j)
            {
                term *= rhs;
            }
            temp += coefficients[i] * term;
        }

        return temp;
    }

    // I wasted 10 min thinking i need to make and friend this :(.
    //  DON'T CHANGE/EDIT THE FOLLOWING DEFINITION:
    template <typename T, int N>
    std::ostream &operator<<(std::ostream &out, Polynomial<T, N> const &pol)
    {
        out << pol[0] << " ";
        for (int i = 1; i <= N; ++i)
        {
            if (pol[i] != 0)
            { // skip terms with zero coefficients
                if (pol[i] > 0)
                {
                    out << "+";
                }
                if (pol[i] == 1)
                {
                }
                else if (pol[i] == -1)
                {
                    out << "-";
                }
                else
                {
                    out << pol[i] << "*";
                }
                out << "x^" << i << " ";
            }
        }
        return out;
    }

} // end namespace HLP3
