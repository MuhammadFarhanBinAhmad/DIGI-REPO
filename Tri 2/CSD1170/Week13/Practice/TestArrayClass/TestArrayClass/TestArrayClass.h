#pragma once
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <vector>


template <typename T>
class Array
{
public:
	Array();
	Array(std::initializer_list<T>);
	//Array(const Array& arr);
	~Array();

	//Array& operator=(Array const& rhs);

	//T const& operator[](size_t index) const;
	T& operator [](size_t index);

	//size_t size() const;                      // accessor for m_size
	void swap(Array& rhs);                    // swap contents of *this and rhs
	void print();

private:
	T* m_elements;
	size_t m_size;
};
