/*!*****************************************************************************
\file matrix.h
\author Nurul Dania Binte Mohd Rizal
\par DP email: nuruldania.b@digipen.edu
\par Course: CSD2125
\par Section: student   
\par Programming Assignment 3
\date 3/11/2021

\brief
Matrix class with proxy class

Matrix(size_type nr, size_type nc)
-  That is, a matrix with rows and 
   columns. The storage for this matrix should be dynamically allocated.

Matrix(Matrix const& rhs)
- Copy constructor

Matrix(Matrix&& rhs) noexcept
- creates a matrix that is a deep copy of matrix rhs .

Matrix(std::initializer_list<std::initializer_list<value_type>>)
- from an initializer list that has rows and
  columns. A runtime_error exception should be thrown if the initializer list doesn't have rows
  of equal size. The runtime_error exception object must be initialized with string "bad
  initializer list" .

~Matrix() noexcept
- Destructor

Matrix& operator=(Matrix const& rhs)
- Assignment operator

Matrix& operator=(Matrix&& rhs) noexcept
- Assignment operator. creates a matrix that is a deep copy of matrix rhs .

size_type get_rows() const noexcept
- returns rows in matrix

size_type get_cols() const noexcept
- returns columns in matrix

proxy-class-for-Matrix operator[](size_type r)
- returns index where row of matrix data. The non-const version 
will return an object of nested proxy class that keeps references to Matrix objects.

proxy-class-for-Matrix-const operator[](size_type r) const
- returns index where row of matrix data. The const version will 
return an object of nested proxy class that keeps references to Matrix const objects.

Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs);
- 1. +: Adding two Matrix<T> objects

Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs);
- 2. -: subtracting two Matrix<T> objects

Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs);
- 3. *: multiplying two Matrix<T> objects

bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs);
- 4. ==: compare two Matrix<T> objects for equality

bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs);
- 5. !=: compare two Matrix<T> objects for inequality

*******************************************************************************/

#ifndef MATRIX_HPP
#define MATRIX_HPP

// include necessary headers ...
#include <iostream>
#include <cstring>
#include <algorithm>    // std::swap
#include <exception>

namespace csd2125 
{

    //define class template Matrix ...
    template <typename T>
    class Matrix 
    {
    public:
        // provide common standard library container type definitions
        // with using keyword ...
        //typedef size_t Matrix<T>::size_type;
        using size_type = size_t;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const reference;
        using pointer = value_type *;
        using const_pointer = const value_type *;
    public:
#if 0
        // To allow clients to access values in an object m of type Matrix m
        // using m[r][c] syntax, define a proxy class.
        // Note that this nested class is simply a type and has no inherent access
        // to any of outer class' members.

        // Therefore, proxy class definition
        // declares 2 data members: a Matrix& data member that references Matrix
        // object instantiating the proxy object and a size_type data member
        // indicating the matrix row.
        
        // Suppose a call to Matrix object's member
        // function (*this).op[](r) returns a proxy object constructed with a
        // reference to *this and the value of (row) index.
        // The proxy class will then define an overload of op[](size_type c) to
        // return the value stored in the Matrix object's data store data[r].

#endif
        class Proxy
        {
            Matrix& parent;
            size_type row;
        public:
            Proxy(Matrix<T> &p, size_type r);
            reference operator[](size_type c);
        };

        // a second nested proxy class definition for Matrix const&
        class ProxyConst
        {
            const Matrix& parent;
            size_type row;
        public:
            ProxyConst(const Matrix<T> &p, size_type r);
            const_reference operator[](size_type c) const;
        };

        // ctors, dtor, copy, and move functions ...
        Matrix(size_type nr, size_type nc);
        Matrix(Matrix const& other);
        Matrix(Matrix&& other) noexcept;
        Matrix(std::initializer_list<std::initializer_list<value_type>>);
        ~Matrix() noexcept;
        Matrix& operator=(Matrix const& other);
        Matrix& operator=(Matrix&& other) noexcept;
        size_type get_rows() const noexcept;
        size_type get_cols() const noexcept;

        Proxy operator[](size_type r);

        ProxyConst operator[](size_type r) const;

    private:
        size_type rows;
        size_type cols;
        pointer* data;

    };

class BadList: public std::exception
{
    virtual const char* what() const throw()
    {
        return "bad initializer list";
    }
} BadList;

class Addition: public std::exception
{
    virtual const char* what() const throw()
    {
        return "operands for matrix addition must have same dimensions";
    }
} Addition;

class Subtraction: public std::exception
{
    virtual const char* what() const throw()
    {
        return "operands for matrix subtraction must have same dimensions";
    }
} Subtraction;

class NotEqual: public std::exception
{
    virtual const char* what() const throw()
    {
        return "number of columns in left operand must match number of rows in right operand";
    }
} NotEqual;


    //define class template Matrix's member functions here ...


    //declare global functions ...
    // 1. +: adding two Matrix<T> objects
    template <typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs);
    // 2. -: subtracting two Matrix<T> objects
    template <typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs);
    // 3. *: multiplying two Matrix<T> objects
    template <typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs);
    // 4. ==: compare two Matrix<T> objects for equality
    template <typename T>
    bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs);
    // 5. !=: compare two Matrix<T> objects for inequality
    template <typename T>
    bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs);

    
    /*!*****************************************************************************
        \brief
        Proxy constructor
        \param p
        Matrix type
        \param r
        size_type for row
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Proxy::Proxy(Matrix<T> &p, size_type r) : parent(p),row (r){}
    
    
    /*!*****************************************************************************
        \brief
        Returns index where row of matrix data. The non-const version 
        will return an object of nested proxy class that keeps references to Matrix objects.
        \param c
        Column number
    *******************************************************************************/
    template <typename T>
    typename Matrix<T>::reference Matrix<T>::Proxy::operator[](size_type c)
    {
        return parent.data[row][c];
    }

    
    /*!*****************************************************************************
        \brief
        Defined for Matrix use. Returns index where row of matrix data. The non-const version 
        will return an object of nested proxy class that keeps references to Matrix objects.
        \param c
        Column number
    *******************************************************************************/
    template <typename T>
    typename Matrix<T>::Proxy Matrix<T>::operator[](size_type r)
    {
        return Proxy(*this, r);
    }

    
    /*!*****************************************************************************
        \brief
        Proxy const Constructor
        \param p
        Matrix type const
        \param r
        size type for row
    *******************************************************************************/
    template <typename T>
    Matrix<T>::ProxyConst::ProxyConst(const Matrix<T> &p, size_type r) : parent(p),row(r){}
    
    
    /*!*****************************************************************************
        \brief
        Returns index where row of matrix data. The const version 
        will return an object of nested proxy class that keeps references to Matrix
        const objects.
        \param c
        Number of column
    *******************************************************************************/
    template <typename T>
    typename Matrix<T>::const_reference Matrix<T>::ProxyConst::operator[](size_type c) const
    {
        return parent.data[row][c];
    }

    
    /*!*****************************************************************************
        \brief
        Defined for Matrix use. Returns index where row of matrix data. The const version 
        will return a object of nested proxy class that keeps references to Matrix 
        const objects.
        \param c
        Column number
    *******************************************************************************/
    template <typename T>
    typename Matrix<T>::ProxyConst Matrix<T>::operator[](size_type r) const
    {
        return ProxyConst(*this, r);
    }
    
    
    /*!*****************************************************************************
        \brief
        Returns number of matrix rows
    *******************************************************************************/
    template<typename T>
    size_t Matrix<T>::get_rows() const noexcept
    {
        return this->rows;
    }

    
    /*!*****************************************************************************
        \brief
        Returns number of matrix columns
    *******************************************************************************/
    template<typename T>
    size_t Matrix<T>::get_cols() const noexcept
    {
        return this->cols;
    }

    
    /*!*****************************************************************************
        \brief
        Matrix constructor.
        That is, a matrix with rows and columns. The storage for this matrix
        should be dynamically allocated.
        \param nr
        Number of rows
        \param nc
        Number of columns
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Matrix(size_type nr, size_type nc) : rows{nr}, cols{nc}
    {
        data = new pointer[rows];
        for(size_type r = 0; r < rows; ++r)
        {
            data[r] = new value_type[cols];
            for(size_type c = 0; c < cols; ++c)
            {
                data[r][c] = T();
            }
        }
    }

    
    /*!*****************************************************************************
        \brief
        Copy constructor
        \param other
        copy rhs data into this matrix data
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Matrix(Matrix const& other)
    {
        rows = other.rows;
        cols = other.cols;
        value_type** tmp_data = new value_type*[rows];
        for(size_type r = 0; r < rows; ++r)
        {
            tmp_data[r] = new value_type[cols];
        }

        for(size_type r = 0; r < rows; ++r)
        {
            for(size_type c = 0; c < cols; ++c)
            {
                tmp_data[r][c] = other.data[r][c];
            }
        }
        data = tmp_data;
    }

    
    /*!*****************************************************************************
        \brief
        Move constructor and deep copy
        \param other
        Deep copy this matrix into other data
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept
    {
        rows = other.rows;
        cols = other.cols;
        data = other.data;

        other.rows = 0;
        other.cols = 0;
        other.data = nullptr; //deleting a nullptr deletes nothing
    }

    
    /*!*****************************************************************************
        \brief
        from an initializer list that has rows and
        columns. A runtime_error exception should be thrown if the initializer list doesn't have rows
        of equal size. The runtime_error exception object must be initialized with string "bad
        initializer list" .
        \param list
        run through the list of that matrix
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>>list) :
    rows{list.size()}, cols{0}  
    {
        for (auto &x : list) // iterate through outer list to find largest inner list
        {
            if (x.size() > cols)
            {
                cols = x.size();
            }
            else if ( x.size() < cols)
            {
                throw BadList;
            }
        }     
        data = new value_type* [rows];  
        auto it = list.begin();         // iterate through outer list 
        for (size_type i = 0; i < rows; i++, it++) 
        {
            data[i] = new value_type[cols];    
            std::copy(it->begin(), it->end(), data[i]); // copy current inner list
        }
    }

    
    /*!*****************************************************************************
        \brief
        Destructor
    *******************************************************************************/
    template <typename T>
    Matrix<T>::~Matrix() noexcept
    {
        for (size_type i{0}; i < rows; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    
    /*!*****************************************************************************
        \brief
        Assignment constructor
        \param other
        Creates a matrix that is a shallow copy of matrix other .
    *******************************************************************************/
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix const& other)
    {
        Matrix tmp(other);
        std::swap(tmp, *this);
        return *this;
    }

    
    /*!*****************************************************************************
        \brief
        Assignment operator.
        \param other
        Creates a matrix that is a deep copy of matrix other .
    *******************************************************************************/
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
    {
        // rmb to free any storage allocated 1st 
        // set this matrix to a "clean" state before moving
        this->~Matrix();   

        rows = other.rows;
        cols = other.cols;
        data = other.data; 
        
        other.rows = 0;
        other.cols = 0;  
        other.data = nullptr;
        return *this;
    }

    //define global functions ...//

    /*!*****************************************************************************
        \brief
        +: adding two Matrix<T> objects
        \param lhs
        L-value Matrix
        \param rhs
        R-value Matrix
    *******************************************************************************/
    template<typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            throw Addition;
        }
        
        Matrix<T> tmp(lhs.get_rows(), lhs.get_cols());
        for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); ++r)
        {
            for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); ++c)
            {
                tmp[r][c] = lhs[r][c] + rhs[r][c];
            }
        }
        return tmp;
    }

    
    /*!*****************************************************************************
        \brief
        -: subtracting two Matrix<T> objects
        \param lhs
        L-value Matrix
        \param rhs
        R-value Matrix
    *******************************************************************************/
    template<typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            throw Subtraction;
        }
        
        Matrix<T> tmp(lhs.get_rows(), lhs.get_cols());
        for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); ++r)
        {
            for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); ++c)
            {
                tmp[r][c] = lhs[r][c] - rhs[r][c];
            }
        }
        return tmp;
    }

    
    /*!*****************************************************************************
        \brief
        *: multiplying two Matrix<T> objects
        \param lhs
        L-value Matrix
        \param rhs
        R-value Matrix
    *******************************************************************************/
    template<typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) 
    {
        if(lhs.get_cols() != rhs.get_rows())
        {
            throw NotEqual;
        }

        Matrix<T> temp(lhs.get_rows(), rhs.get_cols()) ;

        for(typename Matrix<T>::size_type i = 0 ; i < lhs.get_rows() ; i++)
        {
            for(typename Matrix<T>::size_type j = 0 ; j < rhs.get_cols() ; j++)
            {
                temp[i][j] = 0 ;
                for(typename Matrix<T>::size_type k= 0 ; k < rhs.get_rows() ; k++)
                {
                    temp[i][j] = temp[i][j] + (lhs[i][k]*rhs[k][j]) ;
                }
            }
        }
        return temp;
    }

    
    /*!*****************************************************************************
        \brief
        *: multiplying a Matrix<T> object by value
        \param lhs
        L-value Matrix
        \param rhs
        R-value Matrix
    *******************************************************************************/
    template <typename T>
    Matrix<T> operator*(typename Matrix<T>::value_type value, Matrix<T> matrix)
    {
        Matrix<T> tmp(matrix.get_rows(), matrix.get_cols());
        for(typename Matrix<T>::size_type r = 0; r < matrix.get_rows(); ++r)
        {
            for(typename Matrix<T>::size_type c = 0; c < matrix.get_cols(); ++c)
            {
                tmp[r][c] = matrix[r][c] * value;
            }
        }
        return tmp;
    }

    
    /*!*****************************************************************************
        \brief
        ==: compare two Matrix<T> objects for equality
        \param lhs
        L-value Matrix
        \param rhs
        R-value Matrix
    *******************************************************************************/
    template<typename T>
    bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() && lhs.get_cols() != rhs.get_rows())
        {
            return false;
        }
        for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); ++r)
        {
            for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); ++c)
            {
                if(lhs[r][c] != rhs[r][c])
                {
                    return false;
                }
            }
        }
        return true;
    }

    
    /*!*****************************************************************************
        \brief
        !=: compare two Matrix<T> objects for inequality
        \param lhs
        L-value Matrix
        \param rhs
        R-value Matrix
    *******************************************************************************/
    template<typename T>
    bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() == rhs.get_rows() && lhs.get_cols() == rhs.get_cols())
        {
            for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); ++r)
            {
                for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); ++c)
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



