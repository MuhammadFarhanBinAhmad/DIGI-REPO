#pragma once
#include <string>
#include <iostream>
#include <utility>
#include <vector>

struct Item
{
	std::string Name;
	short Amount;
};
class Class
{
protected:
	std::string Name;
	std::string Role;

	short strength, wisdom, intelligence, charisma, agility;
	std::vector<Item> *CharacterInventory;
	std::vector<std::string> Skills;


public:
	~Class();
	virtual void SetStats();
	void SetInventory(std::string N, short A);
	virtual void SetSkills();
	void PrintStats();
};