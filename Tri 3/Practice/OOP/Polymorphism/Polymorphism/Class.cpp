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