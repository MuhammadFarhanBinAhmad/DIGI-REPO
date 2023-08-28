#include "Role.h"

Role::Role() :
	HealthPoint{ 0 },
	Strength{ 0 },
	Intelligence{ 0 },
	Wisdom{ 0 },
	Agility{ 0 },
	Name{ "NULL" },
	Class{ "NULL" }
{

}
Role::Role(const Role& role) :
	HealthPoint{ role.HealthPoint },
	Strength{ role.Strength },
	Intelligence{ role.Intelligence},
	Wisdom{ role.Wisdom},
	Agility{ role.Agility},
	Name{ role.Name },
	Class{ role.Class }
{

}

Role::~Role()
{
}

Role& Role::operator=(const Role& role)
{
	HealthPoint =role.HealthPoint;
	Strength = role.Strength;
	Intelligence = role.Intelligence;
	Wisdom = role.Wisdom;
	Agility = role.Agility;
	Name = role.Name;
	Class = role.Class;

	return *this;
}
