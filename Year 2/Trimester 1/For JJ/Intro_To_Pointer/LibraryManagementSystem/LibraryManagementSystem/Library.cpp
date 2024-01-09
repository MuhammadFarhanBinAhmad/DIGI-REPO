#include "Library.h"

PublishDate::PublishDate(std::string month, short day, short year) : Month(month),Day(day),Year(year){}
PublishDate::PublishDate(const PublishDate& pd): Month(pd.Month), Day(pd.Day), Year(pd.Year){}


PublishDate& PublishDate::operator=(const PublishDate& pd)
{
	if (this != &pd)
	{
		Month = pd.Month;
		Day = pd.Day;
		Year = pd.Year;
	}

	return *this;
}

Book::Book(std::string BookName, std::string AuthorName, PublishDate pd, short isbn, std::string genre)
{
	Book tempbook;

	tempbook.BookName = BookName;
	tempbook.AuthorName = AuthorName;
	tempbook.pd = pd;
	tempbook.ISBN = isbn;
	tempbook.Genre = genre;
}
Book::Book(std::string BookName, std::string AuthorName, const PublishDate& pd, short isbn, std::string genre)
{
	Book tempbook;

	tempbook.BookName = BookName;
	tempbook.AuthorName = AuthorName;
	tempbook.pd = pd;
	tempbook.ISBN = isbn;
	tempbook.Genre = genre;
}
