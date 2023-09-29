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
#include <algorithm>
#include <exception>

namespace HLP3 
{

    template <typename T>
    class Matrix 
    {
        public:
        //Long time no see
        using size_type = size_t;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const reference;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        public:
        // To allow clients to access values in an object m of type Matrix m
        // using m[r][c] syntax, define a proxy class.
        
        
        // Note that this nested class is simply a type and has no inherent access
        // to any of outer class' members. Therefore, proxy class definition
        // declares 2 data members: a Matrix& data member that references Matrix
        // object instantiating the proxy object and a size_type data member
        // indicating the matrix row.

        // Suppose a call to Matrix object's member
        // function (*this).op[](r) returns a proxy object constructed with a
        // reference to *this and the value of (row) index.

        // The proxy class will then define an overload of op[](size_type c) to
        // return the value stored in the Matrix object's data store data[r].
        class Proxy
        {
        private:
            Matrix& parent;
            size_type row;
        public:
            Proxy(Matrix<T> &p, size_type r);
            reference operator[](size_type c);
        };

        // a second nested proxy class definition for Matrix const&
        class ProxyConst
        {
        private:
            const Matrix& parent;
            size_type row;
        public:
            ProxyConst(const Matrix<T> &p, size_type r);
            const_reference operator[](size_type c) const;
        };

        //ctors, dtor, copy, and move functions ...
        //RO5
        Matrix(size_type nr, size_type nc);
        Matrix(Matrix const& rhs);
        Matrix(Matrix&& rhs) noexcept;
        Matrix(std::initializer_list<std::initializer_list<value_type>>);
        ~Matrix() noexcept;
        //Operator
        Matrix& operator=(Matrix const& rhs);
        Matrix& operator=(Matrix&& rhs) noexcept;
        //Helper function
        size_type get_rows() const noexcept;
        size_type get_cols() const noexcept;
        // proxy-class-for-Matrix operator[](size_type r);
        Proxy operator[](size_type r);
        // proxy-class-for-Matrix-const operator[](size_type r) const;
        ProxyConst operator[](size_type r) const;

    private:
        size_type rows;
        size_type cols;
        pointer* data;
    };

    //DECLARING GLOBAL OPERATOR
    ////////////////////////////////////////////////////////////////
    //+: adding 2 matrix objects
    template <typename T>
    Matrix<T> operator+(const Matrix<T> &lhs,const Matrix<T> &rhs);
    //-: subtracting 2 matrix object
    template <typename T>
    Matrix<T> operator-(const Matrix<T> &lhs,const Matrix<T> &rhs);
    //*: multiplying 2 matrix object
    template <typename T>
    Matrix<T> operator*(const Matrix<T> &lhs,const Matrix<T> &rhs);
    //==: compare 2 matrix object if there are equal
    template <typename T>
    Matrix<T> operator==(const Matrix<T> &lhs,const Matrix<T> &rhs);
    //!=: compare 2 matrix object if there are not equal
    template <typename T>
    Matrix<T> operator!=(const Matrix<T> &lhs,const Matrix<T> &rhs);
    ////////////////////////////////////////////////////////////////

    template<typename T>
    Matrix<T>::Proxy::Proxy(Matrix<T> &p, size_type r) : parent(p),row (r){}

    template <typename T>
    typename Matrix<T>::reference Matrix<T>::Proxy::operator[](size_type c) {return parent.data[row][c];}

    template <typename T>
    typename Matrix<T>::Proxy Matrix<T>::operator[](size_type r) {return Proxy(*this,r);}

    template <typename T>
    Matrix<T>::ProxyConst::ProxyConst(const Matrix<T> &p, size_type r) : parent(p),row(r){}

    template <typename T>
    typename Matrix<T>::const_reference Matrix<T>::ProxyConst::operator[](size_type c) const {return parent.data[row][c];}

    template <typename T>
    typename Matrix<T>::ProxyConst Matrix<T>::operator[](size_type r) const {return ProxyConst(*this,r);}

    template<typename T>
    size_t Matrix<T>::get_rows() const noexcept {return this->rows;}

    template<typename T>
    size_t Matrix<T>::get_cols() const noexcept {return this->cols;}

    template<typename T>
    Matrix<T>::Matrix(size_type nr, size_type nc) : rows(nr),cols(nc),data(nullptr)
    {
        
        data = new pointer[rows];

        for (size_type r = 0; r < rows;r++)
        {
            data[r] = new value_type[cols];
            for (size_type c = 0;c < cols ;c++)
            {
                data[r][c] = T();
            }
        }
    }
    template<typename T>
    Matrix<T>::Matrix(Matrix const& rhs)
    {
        this->rows = rhs.rows;
        this->cols = rhs.cols;

        value_type** temp_data = new value_type*[rows];
        for(size_type r = 0; r < rows; ++r)
        {
            temp_data[r] = new value_type[cols];
        }

        for(size_type r = 0; r < rows; ++r)
        {
            for(size_type c = 0; c < cols; ++c)
            {
                temp_data[r][c] = rhs.data[r][c];
            }
        }
        data = temp_data;
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
        rhs.data = nullptr;
    }

    //Didnt know this stuff was legal
    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>> list) : rows{list.size()}, cols{0}
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
                break;
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


    // declare global functions for following operator overloads:
    // 1. +: adding two Matrix<T> objects
    // 2. -: subtracting two Matrix<T> objects
    // 3. *: multiplying two Matrix<T> objects
    // 4. ==: compare two Matrix<T> objects for equality
    // 5. !=: compare two Matrix<T> objects for inequality
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
                        temp[r][c] = temp[c][r] + (lhs[r][k] * rhs[k][c]);
                    }
                }
            }
            return temp;
        }
    }

    template<typename T>
    bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() && lhs.get_cols() != rhs.get_rows())
        {
            return false;
        }

        for (typename Matrix<T>::size_type r = 0 ;r < lhs.get_rows();r++)
        {
            for (typename Matrix<T>::size_type c = 0 ;c < lhs.get_cols();c++)
            {
                //check if all value in matrix is same
                if (lhs[r][c] != rhs [r][c])
                {
                    return false;
                }
            }
        }

        return true;
    }

    template<typename T>
    Matrix<T> operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() == rhs.get_rows() && lhs.get_cols() == rhs.get_cols())
        {
            for (typename Matrix<T>::size_type r =0; r < lhs.get_rows();r++)
            {
                for (typename Matrix<T>::size_type c =0; c < lhs.get_cols();c++)
                {
                    if(lhs[r][c] != rhs[r][c])
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}
#endif
