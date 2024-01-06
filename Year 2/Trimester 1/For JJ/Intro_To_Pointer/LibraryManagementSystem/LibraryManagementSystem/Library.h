#include <string>
#include <iostream>

struct PublishDate
{
	std::string Month;
	short Day, Year;

	PublishDate();
	PublishDate(std::string month, short day, short year);
	PublishDate(const PublishDate& pd);

	PublishDate& operator=(const PublishDate& pd);
};

class Book
{
	std::string BookName;
	std::string AuthorName;
	PublishDate pd;
	short ISBN;
	std::string Genre;

	Book();
	Book(std::string BookName, std::string AuthorName, PublishDate pd, short isbn, std::string genre);
	Book(std::string BookName, std::string AuthorName, const PublishDate& pd, short isbn, std::string genre);

	std::string GetBookName();
	std::string GetAuthorName();
	PublishDate GetPublishDate();
	short GetISBN();
	std::string GetGenre();

	void SetBookName();
	void SetAuthorName();
	void SetPublishDate();
	void SetISBN();
	void SetGenre();
};
