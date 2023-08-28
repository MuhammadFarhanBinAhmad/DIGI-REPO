#include "Class.h"

Class::~Class()
{
	delete[] CharacterInventory;
}
void Class::SetStats()
{
	Name = "NULL";
	Role = "NULL";
	strength = 0;
	wisdom = 0;
	intelligence = 0;
	charisma = 0;
	agility = 0;
}
void Class::SetInventory(std::string N, short A)
{
	Item* I = new Item;
	I->Name = N;
	I->Amount = A;
	CharacterInventory->push_back(*I);
}
void Class::SetSkills()
{
	Skills.push_back("NULL");
}
void Class::PrintStats()
{
	std::cout <<
		"Role:" << Name << '\n' <<
		"Name:" << Role << '\n' << '\n' <<
		"Stats" << '\n'<<
		"Strength:" << strength << '\n' <<
		"Wisdom:" << wisdom << '\n' <<
		"Intelligence:" << intelligence << '\n' <<
		"Charisma:" << charisma << '\n' <<
		"Agility:" << agility << '\n' << '\n';

	std::cout << "Skills" << '\n';
	for (std::string s : Skills)
	{
		std::cout << s << std::endl;
	}
	std::cout << '\n';
}