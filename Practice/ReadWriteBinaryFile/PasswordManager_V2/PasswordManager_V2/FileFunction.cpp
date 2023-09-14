#include "FileFunction.h"
#include "Data.h"

void DecipherPassword()
{
	std::unique_ptr<PasswordData> pd(new PasswordData());
	pd->DecipherFile("./Password.cat");
}
void AddPassword()
{
	std::string Website, Password;
	std::unique_ptr<PasswordData> pd(new PasswordData());

	std::cout << "Enter Website: ";
	std::cin >> Website;
	std::cout << "Enter Password: ";
	std::cin >> Password;

	pd->SetData(Website, Password);
	pd->WriteFile("./Password.cat");
}
void EditPassword()
{
	std::unique_ptr<PasswordData> pd(new PasswordData());
	pd->PrintAllWebsite();
	std::cout << "Enter website index to edit password\n";

	int wb = 0;
	std::cin >> wb;

	pd->EditPassword("./Password.cat",wb);

}
void DeletePassword() 
{
	std::unique_ptr<PasswordData> pd(new PasswordData());
	pd->PrintAllWebsite();
	std::cout << "Enter website index to delete password\n";

	int wb = 0;
	std::cin >> wb;

	pd->DeletePassword("./Password.cat",wb);
}
void ViewPassword()
{
	std::unique_ptr<PasswordData> pd(new PasswordData());
	pd->PrintAllWebsite();
	std::cout << "Enter website index to view password\n";

	int wb = 0;
	std::cin >> wb;

	pd->PrintPassword(wb);

}
void ViewAllPassword()
{
	std::unique_ptr<PasswordData> pd(new PasswordData());
	pd->PrintAllContent();
}
