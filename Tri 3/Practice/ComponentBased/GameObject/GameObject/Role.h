#pragma once
#include <string>
#include <iostream>

class Role
{
public:
	Role();
	Role(const Role& role);
	~Role();

	Role& operator=(const Role& role);

private:
	short HealthPoint;
	short Strength;
	short Intelligence;
	short Wisdom;
	short Agility;

	std::string Name;
	std::string Class;
};
