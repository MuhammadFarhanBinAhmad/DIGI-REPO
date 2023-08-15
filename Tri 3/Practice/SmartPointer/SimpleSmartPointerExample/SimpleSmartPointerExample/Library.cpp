#include "Library.h"
#include <iostream>
#include <vector>

void Library::DisplayAllBook()
{
	for (Book i : list_Book)
	{
		std::cout
			<< i.GetAurthor() << '\n'
			<< i.GetTitle() << '\n'
			<< i.GetISBN() << '\n'
			<< i.GetLender() << '\n'
			<< i.GetAvailability() << '\n'
			<< std::endl;
	}
}
void Library::DisplayBooks(int64_t ISBN)
{
	for (Book i : list_Book)
	{
		if (i.GetISBN() == ISBN)
		{
			std::cout
				<< i.GetAurthor() << '\n'
				<< i.GetTitle() << '\n'
				<< i.GetISBN() << '\n'
				<< i.GetLender() << '\n'
				<< i.GetAvailability() << '\n'
				<< std::endl;
		}
	}
}
void Library::SetBookLender(int64_t ISBN, std::string Lender)
{

	for (Book i : list_Book)
	{
		if (i.GetISBN() == ISBN)
		{
			i.SetLender(Lender);
			i.SetAvailability(true);
		}
	}

	std::cout << "Book does not exist" << std::endl;
}

