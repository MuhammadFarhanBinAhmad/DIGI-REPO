/*****************************************************************//**
 * \file	matrix-proxy.hpp
 * \brief	Implement proxy class of a 2d array using move semantics
 *
 * \author	FarhanAhmad(ID:2200544)(EMAIL:2200544@sit.SingaporeTech.edu.sg)
 * 
 * \note    Trying out something new in how i comment. Atop the standard comments, add bit of thoughts and opinion.
 *          Reflection time(Basically record down my emotion and thoughts for each line/function. I know emotional attachment and connection can help one rememeber better.So why no try for coding)
 *          Split to 2 section doxygen part and self reflection part.
 *
 * \date	30-SEP-2023
***********************************************************************/
#ifndef MATRIX_PROXY_HPP
#define MATRIX_PROXY_HPP

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
        //Tbh,while I never usually use them, i do understand their use,i rarely use them on my own
        //or other school project. I not sure why i dont want to use them tho. But all mean it makes life easier but it seem a part my seem stubborn to use them. Hmm
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

        //ctors, dtor, copy, and move functions ...
        //Rule of 5
        Matrix(size_type nr, size_type nc);
        Matrix(Matrix const& other);
        //Move constructor. Should explore this more in the future and what its use and restriction
        Matrix(Matrix&& other) noexcept;
        Matrix(std::initializer_list<std::initializer_list<value_type>> list);
        ~Matrix() noexcept;
        //Operator
        Matrix& operator=(Matrix const& rhs);
        Matrix& operator=(Matrix&& rhs) noexcept;
        //Helper function
        size_type get_rows() const noexcept;
        size_type get_cols() const noexcept;
        //Proxy looks cool. Still not too confident in implementing it. Need to make more proxy class in the future.Wonder if there
        //is any other type of proxy class
        // proxy-class-for-Matrix operator[](size_type r);
        Proxy operator[](size_type r);
        // proxy-class-for-Matrix-const operator[](size_type r) const;
        ProxyConst operator[](size_type r) const;

    private:
        size_type rows;
        size_type cols;
        pointer* data;
    };

    //TBH i thought i could just std::cout to make it work. But it didnt so not too sure if legit need this or maybe i set something wrong.
    //Senior recommend me to make it anyway cause its good practice anyway.
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
    bool operator==(const Matrix<T> &lhs,const Matrix<T> &rhs);
    //!=: compare 2 matrix object if there are not equal
    template <typename T>
    bool operator!=(const Matrix<T> &lhs,const Matrix<T> &rhs);
    ////////////////////////////////////////////////////////////////

    /*
    Thoughts:This is really just the same thing as that operator assignment in HLP2.Which meant the same struggle occured.
             Mostly syntax understanding and what not. Although this seem more "technical" and in depth so was harder for me to see.
             Again,like the bitset assignment, need spend more time making different variant so that can have a better understanding and
             fimilarizing with the syntax.Wish it was so touch and go. Sadly in uni i dont have much time to consolidate.
    */

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
    
    
    template <typename T>
    typename Matrix<T>::reference Matrix<T>::Proxy::operator[](size_type c)
    {
        return parent.data[row][c];
    }

    template <typename T>
    typename Matrix<T>::Proxy Matrix<T>::operator[](size_type r)
    {
        return Proxy(*this, r);
    }

    template <typename T>
    Matrix<T>::ProxyConst::ProxyConst(const Matrix<T> &p, size_type r) : parent(p),row(r){}
    
    template <typename T>
    typename Matrix<T>::const_reference Matrix<T>::ProxyConst::operator[](size_type c) const
    {
        return parent.data[row][c];
    }

    
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
    Matrix<T>::Matrix(Matrix const& rhs)
    {
        this->rows = rhs.rows;
        this->cols = rhs.cols;

        value_type** temp_data = new value_type*[rows];

        for(size_type r = 0; r < rows; r++)
        {
            temp_data[r] = new value_type[cols];
        }

        for(size_type r = 0; r < rows; r++)
        {
            for(size_type c = 0; c < cols; c++)
            {
                temp_data[r][c] = rhs.data[r][c];
            }
        }
        data = temp_data;
    }

    
    /*!*****************************************************************************
        \brief
        Move constructor and deep copy
        \param other
        Deep copy this matrix into other data
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Matrix(Matrix&& rhs) noexcept
    {
        this->rows = rhs.rows;
        this->cols = rhs.cols;
        this->data = rhs.data;

        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = nullptr; //deleting a nullptr deletes nothing
    }

    
    /*!*****************************************************************************
        \brief
        Form matrix using a initializer_list list in a initializer_list(cool)
        If the column is incorrect, will throw exception error
        \param list
        run through the list of that matrix
    *******************************************************************************/
    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>>list) : rows{list.size()}, cols{0}  
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

        auto it = list.begin();

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
        for (size_type i = 0 ; i < rows; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    
    /*!*****************************************************************************
        \brief
        Assignment constructor
        \param rhs
        Create a shallow copy
    *******************************************************************************/
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix const& rhs)
    {
        Matrix tmp(rhs);
        std::swap(tmp, *this);
        return *this;
    }

    
    /*!*****************************************************************************
        \brief
        Assignment operator.
        \param rhs
        Creates a matrix that is a deep copy of matrix other .
    *******************************************************************************/
    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) noexcept
    {
        // rmb to free any storage allocated 1st 
        // set this matrix to a "clean" state before moving
        this->~Matrix();   

        this->rows = rhs.rows;
        this->cols = rhs.cols;
        this->data = rhs.data; 
        
        rhs.rows = 0;
        rhs.cols = 0;  
        rhs.data = nullptr;

        return *this;
    }


    /*!*****************************************************************************
        \brief
        adding 2 matrix 
        \param lhs
        L-value matrix
        \param rhs
        R-value matrix
    *******************************************************************************/
    template<typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            //Wrong size. Cant add them together
            throw Addition;
        }
        
        Matrix<T> temp(lhs.get_rows(), lhs.get_cols());

        for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); r++)
        {
            for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); c++)
            {
                temp[r][c] = lhs[r][c] + rhs[r][c];
            }
        }
        return temp;
    }

    
    /*!*****************************************************************************
        \brief
        subtract 2 matrix
        \param lhs
        L-value matrix
        \param rhs
        R-value matrix
    *******************************************************************************/
    template<typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if(lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            //Wrong size. Cant minus them together
            throw Subtraction;
        }
        
        Matrix<T> temp(lhs.get_rows(), lhs.get_cols());

        for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); r++)
        {
            for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); c++)
            {
                temp[r][c] = lhs[r][c] - rhs[r][c];
            }
        }
        return temp;
    }

    
    /*!*****************************************************************************
        \brief
        multiply 2 matrix
        \param lhs
        L-value matrix
        \param rhs
        R-value matrix
    *******************************************************************************/
    template<typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) 
    {
        if(lhs.get_cols() != rhs.get_rows())
        {
            //Wrong size. Cant multiple them together
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
        multiply 2 matrix
        \param lhs
        L-value matrix
        \param rhs
        R-value matrix
    *******************************************************************************/
    template <typename T>
    Matrix<T> operator*(typename Matrix<T>::value_type value, Matrix<T> matrix)
    {
        Matrix<T> temp(matrix.get_rows(), matrix.get_cols());

        for(typename Matrix<T>::size_type r = 0; r < matrix.get_rows(); r++)
        {
            for(typename Matrix<T>::size_type c = 0; c < matrix.get_cols(); c++)
            {
                temp[r][c] = matrix[r][c] * value;
            }
        }
        return temp;
    }

    
    /*!*****************************************************************************
        \brief
        Check 2 matrix are the same
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

        for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); r++)
        {
            for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); c++)
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
        Check if 2 matrix are unequal
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
            for(typename Matrix<T>::size_type r = 0; r < lhs.get_rows(); r++)
            {
                for(typename Matrix<T>::size_type c = 0; c < lhs.get_cols(); c++)
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
