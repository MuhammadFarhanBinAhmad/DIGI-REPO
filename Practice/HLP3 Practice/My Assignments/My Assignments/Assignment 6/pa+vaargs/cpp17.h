/*!*****************************************************************************
\file cpp11.h
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 6
\date 26/11/2021

\brief
Definition of a sequence type, c17.
Implemented as cpp17.h .
Conforms to the C++17 standard.
Single function template that includes the if constexpr statement.
Contains keywords:
    - class
    - struct
    - typedef
Keyword using is permitted only once.
Must not contain multiplication ( * ) or addition ( + ) operators; consider bitwise
operators.

*******************************************************************************/
#ifndef CPP_17
#define CPP_17

/*!*****************************************************************************
    \brief
    make_sequence_impl returns a struct index_sequence.
*******************************************************************************/
template<size_t M, size_t... Rest>
// make_sequence_impl returns a struct index_sequence.
constexpr auto make_sequence_impl() {
    // base case
    if constexpr (M == 0) {
        // -> make_sequence_impl<0,3,2,1>() -> index_sequence<8,4,2,1>{}
        return index_sequence<(static_cast<size_t>(1) << Rest)..., 1>{};
    // recursive case
    } else {
        // e.g. make_sequence_impl<3>() -> make_sequence_impl<2,3>() -> make_sequence_impl<1,3,2>() -> base case
        return make_sequence_impl<M-1, Rest..., M>();
    }
}

/*!*****************************************************************************
    \brief
    decltype returns the return type of make_sequence_impl().
*******************************************************************************/
template<size_t M>
// decltype returns the return type of make_sequence_impl().
using make_sequence = decltype(make_sequence_impl<M>());

#endif