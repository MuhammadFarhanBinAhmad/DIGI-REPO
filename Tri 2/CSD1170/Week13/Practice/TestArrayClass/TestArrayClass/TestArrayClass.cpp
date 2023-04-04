// TestArrayClass.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "TestArrayClass.h"

template<typename T>
Array<T>::Array()
{
}
template<typename T>
Array<T>::Array(std::initializer_list<T> rhs) : m_elements{ new T[rhs.size()]{} }, m_size{rhs.size()}
{
	typename std::initializer_list<T>::iterator start = rhs.begin();

	for (size_t i = 0; i < rhs.size(); i++)
	{
		m_elements[i] = *start;
		start++;
	}
}

template<typename T>
T& Array<T>::operator[](size_t index)
{
	for (size_t i = 0; i < index; i++)
	{
		m_elements++;
	}
	return *m_elements;
}

template<typename T>
Array<T>::~Array()
{
	delete[] m_elements;
}
template<typename T>
void Array<T>::swap(Array& rhs)
{
	T* temp = m_elements;

	m_elements = rhs.m_elements;
	rhs.m_elements = temp;

	size_t temp_ST = m_size;
	m_size = rhs.m_size;
	rhs.m_size = temp_ST;

}


template<typename T>
void Array<T>::print()
{
	for (size_t i = 0; i < m_size; i++)
	{
		std::cout << m_elements[i] << std::endl;
	}
}


//template <typename T>
//Array<T>& Array<T>::operator=(Array const& rhs) 
//{
//	Array<T> copy{ rhs };
//	swap(copy);
//	return *this;
//}


int main()
{
	std::initializer_list<int> integer_List1{ 1,2,3,4,5,6,7,8 };
	std::initializer_list<int> integer_List2{ 5,1,2,6,7,2,3 };

	Array<int> test1(integer_List1);
	Array<int> test2(integer_List2);

	std::cout << test1[1];

	//test1.print();
	//test1.swap(test2);
	//test1.print();

	/*Array<int> test3;
	test3 = test1;*/

	//test3.print();
	/*
	* int n{24};
	char const *str{"wombat"};
	double x{9.5};
	std::cout << '<' << std::right << std::setfill('x') << std::setw(5) << n 
				<< str << x << '3' << '>';
	//print out <xxx24wombat9.53>
	why is xxx24 and not xxxxx24 is because the setw(5) "reserve" 5 char to be use by the set fill and n
	*/
}
