#include "Warrior.h"

void Warrior::SetStats()
{
	Name = "Gimli";
	Role = "Warrior";
	strength = 18;
	wisdom = 12;
	intelligence = 10;
	charisma = 10;
	agility = 14;
}
void Warrior::SetSkills()
{
	Skills.push_back("Brave");
	Skills.push_back("Improved Critical");
	Skills.push_back("Martial Advantage");
	Skills.push_back("Protection");
	Skills.push_back("Keen Mind");
}