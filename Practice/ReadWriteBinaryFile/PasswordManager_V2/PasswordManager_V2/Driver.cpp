#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Data.h"
#include "FileFunction.h"

/*TODO*/
/*
 *Button input for different features 
 *Show all website first, then user can select which website password to view
 *Enable user to select website and edit current password
 *Enable user to select and delete website password
 */
int InputCommand = 0;

enum CommandCode
{
	ADDPASSWORD = 1,
	EDITPASSWORD,
	DELETEPASSWORD,
	VIEWPASSWORD,
	VIEWALLPASSWORD,
	EXITPROGRAM
};

int main()
{
	DecipherPassword();
	while (InputCommand != EXITPROGRAM)
	{
		std::cout << "What do you wish to do ?\n"
			<< "1: ADDPASSWORD\n"
			<< "2: EDITPASSWORD\n"
			<< "3: DELETEPASSWORD\n"
			<< "4: VIEWPASSWORD\n"
			<< "5: VIEWALLPASSWORD\n"
			<< "6: EXITPROGRAM\n";

		std::cin >> InputCommand;

		switch (InputCommand)
		{
		case ADDPASSWORD:
			AddPassword();
			break;
		case EDITPASSWORD:
			EditPassword();
			break;
		case DELETEPASSWORD:
			DeletePassword();
			break;
		case VIEWPASSWORD:
			ViewPassword();
			break;
		case VIEWALLPASSWORD:
			ViewAllPassword();
			break;
		}

	}

	return 0;
}
