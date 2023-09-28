// Don't forget file-header and function-level Doxygen documentation blocks!!!

// First, define the class template. Then, define the member functions of the class template
// OUTSIDE the class definition. The automatic grader will not be able to check for this - 
// however, the manual grader can. Occurrences of EACH such function defined in the class definition
//  will result in a deduction of ONE LETTER GRADE!!! You're forewarned!!!

// This is how you should implement the assignment:

#ifndef MATRIX_PROXY_HPP
#define MATRIX_PROXY_HPP

// include necessary headers ...
#include <iostream>
#include <cstring>
#include <algorithm>    // std::swap
#include <exception>

namespace HLP3 
{

    template <typename T>
    class Matrix 
    {
        public:
        // provide common standard library container type definitions
        // with using keyword ...
        using size_type = size_t;
        using value_type = T;
        using pointer = value_type *;
        using const_pointer = const value_type*;
        using iterator = pointer;
        using const_iterator = const_pointer;

        public:
        // To allow clients to access values in an object m of type Matrix m
        // using m[r][c] syntax, define a proxy class.
        // Note that this nested class is simply a type and has no inherent access
        // to any of outer class' members. Therefore, proxy class definition
        // declares 2 data members: a Matrix& data member that references Matrix
        // object instantiating the proxy object and a size_type data member
        // indicating the matrix row. Suppose a call to Matrix object's member
        // function (*this).op[](r) returns a proxy object constructed with a
        // reference to *this and the value of (row) index.
        // The proxy class will then define an overload of op[](size_type c) to
        // return the value stored in the Matrix object's data store data[r].
        // a second nested proxy class definition for Matrix const&
        // ctors, dtor, copy, and move functions ...
        Matrix(size_type nr, size_type nc) : rows(nr),cols(nc),data(nullptr);
        Matrix(Matrix const& rhs);
        Matrix(Matrix&& rhs) noexcept;
        Matrix(std::initializer_list<std::initializer_list<value_type>>);
        ~Matrix() noexcept;
        Matrix& operator=(Matrix const& rhs);
        Matrix& operator=(Matrix&& rhs) noexcept;
        size_type get_rows() const noexcept;
        size_type get_cols() const noexcept;
        proxy-class-for-Matrix operator[](size_type r);
        proxy-class-for-Matrix-const operator[](size_type r) const;

        private:
        size_type rows;
        size_type cols;
        pointer data;
        
    };
    template<typename T>
    Matrix<T>::Matrix(size_type nr, size_type nc) : rows(nr),cols(nc),data(nullptr)
    {
        
        data = new value_type*[row];

        for (size_type i = 0; i < rows;i++)
        {
            data[i] = new value_type[cols];
        }
    }
    template<typename T>
    Matrix<T>::Matrix(Matrix const& rhs)
    {
        this->rows = rhs.rows;
        this->cols = rhs.cols;

        pointer* tmp_data = new pointer[this->rows];

        for (size_type i = 0; i < this->rows; i++)
        {
            tmp_data[i] = new value_type[this->cols];
        }

        for (size_type i = 0; i < this->rows; i++)
        {
            for (size_type j = 0;i <  this->cols;i++)
            {
                tmp_data[i][j] = rhs.data[i][j];//get other matrix value
            }
        }
    }
    //MOVE CONSTRUCTOR(Imma steal that)
    //Enable resources owned by an rvalue object to be moved to an lvalue without copying - Microsoft
    //Move constructor basically help avoid unnecassry copying data
    template<typename T>
    Matrix<T>::Matrix(Matrix&& rhs) noexcept
    {
        this->rows = rhs.rows;
        this->cols = rhs.cols;
        this->data = rhs.data;

        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = 0;
    }


    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>>list) : rows{list.size()}, cols{0}
    {
        for (auto &m: list)
        {
            if (m.size() > this->cols)
            {
                this->cols = m.size();
            }
            else if (m.size() < this->cols)
            {
                std::cout << "BadList";
            }
        }

        data = new value_type*[this->rows];
        auto it = list.begin();

        for (size_type i = 0; i < this->rows;i++,it++)
        {
            data[i] = new value_type[this->cols];
            std::copy(it->begin(),it->end(),data[i]);//copy current inner list
        }
    }

    template<typename T>
    Matrix<T>::~Matrix() noexcept
    {
        for (size_type i = 0; i < this->rows;i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    //Standard copy constructor
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix const& rhs)
    {
        Matrix temp(rhs);
        std::swap(temp, *this);
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) noexcept
    {
        //Need to free allocated 1st
        this->~Matrix();

        this->rows = rhs.rows;
        this->cols = rhs.cols;
        this->data = rhs.data;
        
        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = nullptr;

        return *this;
    }

    template<typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            std::cout << "Addition wrong size";
        }
        else
        {
            Matrix<T> temp(lhs.get_rows(),lhs.get_cols());

            for (typename Matrix<T>::size_type r = 0; r < lhs.get_rows();r++)
            {
                for (typename Matrix<T>::size_type c = 0; c < lhs.get_cols();c++)
                {
                    temp[r][c] = lhs[r][c] + rhs[r][c];
                }
            }
            return temp;
        }
    }
    template<typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            std::cout << "Subtraction wrong size";
        }
        else
        {
            Matrix<T> temp(lhs.get_rows(),lhs.get_cols());

            for (typename Matrix<T>::size_type r = 0; r < lhs.get_rows();r++)
            {
                for (typename Matrix<T>::size_type c = 0; c < lhs.get_cols();c++)
                {
                    temp[r][c] = lhs[r][c] - rhs[r][c];
                }
            }
            return temp;
        }
    }

    template<typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            std::cout << "Multiplication wrong size";
        }
        else
        {
            Matrix<T> temp(lhs.get_rows(),lhs.get_cols());

            for (typename Matrix<T>::size_type r = 0; r < lhs.get_rows();r++)
            {
                for (typename Matrix<T>::size_type c = 0; c < lhs.get_cols();c++)
                {
                    temp[r][c] = 0;
                    for (typename Matrix<T>::size_type k = 0; k < rhs.get_rows();k++)
                    {
                        temp[r][c] = temp[c][j] + (lhs[r][k] * rhs[k][c]);
                    }
                }
            }
            return temp;
        }
    }

    template<typename T>
    Matrix<T> operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        
    }

    template<typename T>
    Matrix<T> operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {

    }
}
// declare global functions for following operator overloads:
// 1. +: adding two Matrix<T> objects
// 2. -: subtracting two Matrix<T> objects
// 3. *: multiplying two Matrix<T> objects
// 4. ==: compare two Matrix<T> objects for equality
// 5. !=: compare two Matrix<T> objects for inequality
#endif
