/*!*****************************************************************************
\file cpp11.h
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 6
\date 26/11/2021

\brief
Definition of a sequence type, c11.
Implemented as cpp11.h.
Conforms to the C++11 standard.
Based on a single base class template and one partial specialization.
Keyword using is permitted no more than 3 times.

*******************************************************************************/
#ifndef CPP_11
#define CPP_11

/*!*****************************************************************************
    \brief
    Make sequence implementation class. Base class template (recursive case)
*******************************************************************************/
// base class template (recursive case)
template<size_t M, size_t... Rest>
class make_sequence_impl {
    public:
        // recursion in play
        // e.g. make_sequence_impl<3>::s -> make_sequence_impl<2,3>::s -> make_sequence_impl<1,3,2>::s -> base case
        using s = typename make_sequence_impl<M-1, Rest..., M>::s;
};

/*!*****************************************************************************
    \brief
    Make sequence implementation class. Partial specialisation (base case)
*******************************************************************************/
// partial specialisation (base case)
template<size_t... Rest>
class make_sequence_impl<0, Rest...> {
    public:
        // cont.
        // -> make_sequence_impl<0,3,2,1>::s -> index_sequence<8,4,2,1>
        using s = index_sequence<(static_cast<size_t>(1) << Rest)..., 1>;
};

/*!*****************************************************************************
    \brief
    equivalent to: using make_sequence = index_sequence<A,B,C,...>
*******************************************************************************/
template<size_t M>
// equivalent to:
// using make_sequence = index_sequence<A,B,C,...>
using make_sequence = typename make_sequence_impl<M>::s;

#endif