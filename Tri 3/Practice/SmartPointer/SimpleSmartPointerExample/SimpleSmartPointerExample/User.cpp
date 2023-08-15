#include "User.h"

void User::Display_BooksBorrowed()
{
	for (Book i : Book_Borrowed)
	{
		std::cout << i.GetTitle() << std::endl;
	}
}