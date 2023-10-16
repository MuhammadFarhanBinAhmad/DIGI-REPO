// CountTotalElement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <initializer_list>

template<typename T>
int count_total_element(const std::initializer_list<std::initializer_list<T>>& list)
{
	int total = 0;;

	for (const std::initializer_list<T>& inner : list)
	{
		std::cout << "Element in list: ";
		for (const T& ele: inner)
		{
			std::cout << ele << ' ';
		}
		std::cout << '\n';
		total += inner.size();
	}
	return total;
}

int main()
{
	std::initializer_list<std::initializer_list<int>> list_01{ {2,3,5},{2,354},{3,4,5,6} };
	std::initializer_list<std::initializer_list<float>> list_02{ {2.41,3.35,7.123},{2.1231,354.432421},{3.123,4.745,5.21,6.231} };

	int total_int = count_total_element(list_01);

	std::cout<< "Total int: " << total_int;
	std::cout << '\n';

	int total_float = count_total_element(list_02);

	std::cout << "Total float: "<< total_float;
}
